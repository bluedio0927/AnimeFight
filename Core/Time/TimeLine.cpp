#include "TimeLine.h"
#ifdef _DEBUG
#include <iostream>
#endif
namespace AnimeFight
{
	TimeLine::TimeLine(size_t In_TimepointNums)
		:m_bEnter(false), m_bLeave(false), m_stayTimePointIndex(0), m_thread(nullptr)
	{
		m_vecTimeNodes.reserve(In_TimepointNums+1);
		m_vecTimeNodesLeaveFlag.reserve(In_TimepointNums+1);
		for (size_t i = 0; i < In_TimepointNums + 1; ++i)
		{
			m_vecTimeNodes.emplace_back(i);
			m_vecTimeNodesLeaveFlag.push_back(Unknown);
		}
	}

	TimeLine::~TimeLine()
	{
		Cancel();
		if (m_thread)
		{
			m_thread->join();
			delete m_thread;
			m_thread = nullptr;
		}
	}

	size_t TimeLine::GetTimeNodeNums()
	{
		return m_vecTimeNodes.size();
	}

	size_t TimeLine::GetNowStayPointIndex()
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		return m_stayTimePointIndex;
	}

	bool TimeLine::SetTimeNodeStayTimeout(size_t In_NodeIndex, long long In_Timeoutms)
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		if (In_NodeIndex < GetTimeNodeNums())
		{
			m_mapTimeNodeLeaveMode[In_NodeIndex] = In_Timeoutms;
			return true;
		}
		else
			return false;
	}

	bool TimeLine::GetTimeNodeStayTimeout(size_t In_NodeIndex, long long &Out_Timeoutms)
	{
		const auto &iter = m_mapTimeNodeLeaveMode.find(In_NodeIndex);
		if (iter != m_mapTimeNodeLeaveMode.end())
		{
			Out_Timeoutms = iter->second;
			return true;
		}
		else
			return false;
	}

	bool TimeLine::UnSetTimeNodeStayTimeout(size_t In_NodeIndex)
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		const auto &iter = m_mapTimeNodeLeaveMode.find(In_NodeIndex);
		if (iter != m_mapTimeNodeLeaveMode.end())
		{
			m_mapTimeNodeLeaveMode.erase(iter);
			return true;
		}
		else
			return false;
	}

	void TimeLine::PushCMD(CMDTYPE In_CMD)
	{
		{
			std::lock_guard<std::mutex> autolock(m_mutex);
			m_queNODECMD.push(In_CMD);
		}
		m_cvPop.notify_one();
	}

	void TimeLine::Enter()
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		m_bEnter = true;
		//Start Pop CMD Queue Thread...
		m_thread = new std::thread(std::bind(&TimeLine::DoPopCMD, this));
	}

	TimeLine::NodeState TimeLine::Next()
	{
		NodeState state(Unknown);
		std::unique_lock<std::mutex> unilck(m_mutex);
		if (!m_bLeave && m_bEnter)
		{
			auto NextNodeIndex = m_stayTimePointIndex + 1;
			if (NextNodeIndex == GetTimeNodeNums())// Final Node...
				DoLeave();
			else
				state = GotoNode(unilck, NextNodeIndex);//Next Node...
		}
		if (m_bLeave)
			state = End;
		return state;
	}

	bool TimeLine::ForwardTo(size_t In_PointIndex)
	{
		std::unique_lock<std::mutex> unilck(m_mutex);
		bool bRet(false);
		if (m_bEnter && !m_bLeave && In_PointIndex > m_stayTimePointIndex)
		{
			if (In_PointIndex >= m_vecTimeNodes.size())
				DoLeave();
			else
				GotoNode(unilck, In_PointIndex);//GoTo Node...
		}
		return bRet;
	}

	bool TimeLine::IsEnd()
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		return m_bLeave;
	}

	void TimeLine::Cancel()
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		DoLeave();
	}

	//private...
	void TimeLine::DoPopCMD()
	{
		auto NeedCalTimeout = [&](long long &Out_leavems)
		{
			return GetTimeNodeStayTimeout(m_stayTimePointIndex, Out_leavems) && Out_leavems;
		};

		auto timeoutpredc = [&](long long In_Leavems, long long &stayms)
		{
			//重新計算一次判斷停留時間是否已滿足條件
			stayms = m_vecTimeNodes[m_stayTimePointIndex].GetStayDurationMs();
			if (stayms >= In_Leavems && m_vecTimeNodes[m_stayTimePointIndex].GetSate() == TimeNode::Staying)
				m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = NodeState::Passed_TimeOut;
			return m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] || m_bLeave;
		};

		auto defaultpredc = [&]
		{
			long long Leavems(0);
			return (!m_queNODECMD.empty() || m_bLeave ||
					NeedCalTimeout(Leavems)/*在進行wait時, 如果因為m_stayTimePointIndex更改後被Notify, 檢查是否有timeout, 有就強制離開*/);
		};

		// Start Run DoPopCMD....
		while (!m_bLeave)
		{
			std::unique_lock<std::mutex> unilck(m_mutex);
			if (!m_queNODECMD.empty())
			{
				switch (m_queNODECMD.front())
				{
				case CMDTYPE::GoNext:
					if(m_vecTimeNodes[m_stayTimePointIndex].GetSate() == TimeNode::Staying)
						m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = NodeState::Passed_Success;
					break;

				case CMDTYPE::Hang:
					m_vecTimeNodes[m_stayTimePointIndex].Hang(true);
					break;

				case CMDTYPE::Keep:
					m_vecTimeNodes[m_stayTimePointIndex].Hang(false);
					break;
				}
				m_queNODECMD.pop();
			}
			else
			{
				long long Leavems(0);
				//Check時間節點的條件
				if (NeedCalTimeout(Leavems))
				{
					long long stayms(0);
					if (!timeoutpredc(Leavems, stayms))//計算判斷停留時間是否已滿足條件
					{
						//計算時間差值直接wait
						m_cvPop.wait_for(unilck, std::chrono::milliseconds(Leavems - stayms), defaultpredc);
					}
				}
				else
					m_cvPop.wait(unilck, defaultpredc);//若是無Timeout的Node跟一開始沒事做時卡在這
			}//end if (!m_queNODECMD.empty())

			if(m_vecTimeNodesLeaveFlag[m_stayTimePointIndex])//Passed的狀態才叫醒
				m_cvNext.notify_one();//叫醒Block住的Client Function
		}
	}

	TimeLine::NodeState TimeLine::GotoNode(std::unique_lock<std::mutex> &unilck, size_t Index)
	{
		NodeState State(Unknown);
		if ((m_vecTimeNodes[Index].GetSate() == TimeNode::None) &&
			(Index - 1 == 0 /*前一個節點是起點就跳過*/|| (m_vecTimeNodes[Index - 1].GetSate() == TimeNode::Passed)))//確認已離開前一個節點
		{
			//Enter...
			m_vecTimeNodes[Index].Enter();
			m_stayTimePointIndex = Index;//Move~~

			m_cvPop.notify_one();
			long long Out_ms;
			const auto &iter = m_mapTimeNodeLeaveMode.find(Index);
			if (GetTimeNodeStayTimeout(Index, Out_ms))
			{
				m_cvNext.wait(unilck, [&] { return (m_vecTimeNodesLeaveFlag[Index]  || m_bLeave); });
			}
			else
				m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = NodeState::Passed_Success;

			State = m_vecTimeNodesLeaveFlag[m_stayTimePointIndex];
			//Leave...
			m_vecTimeNodes[Index].Leave();
		}
		return State;
	}

	void TimeLine::DoLeave()
	{
		m_bLeave = true;
		m_cvPop.notify_one();
		m_cvNext.notify_all();
	}
}