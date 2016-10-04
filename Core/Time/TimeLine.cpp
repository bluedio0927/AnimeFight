#include "TimeLine.h"
#ifdef _DEBUG
#include <iostream>
#endif
namespace AnimeFight
{
	TimeLine::TimeLine(size_t In_TimepointNums)
		:m_bEnter(false), m_bLeave(false), m_stayTimePointIndex(0), m_thread(nullptr)
	{
		m_vecTimeNodes.reserve(In_TimepointNums);
		m_vecTimeNodesLeaveFlag.reserve(In_TimepointNums);
		for (size_t i = 0; i < In_TimepointNums; ++i)
		{
			m_vecTimeNodes.emplace_back(i);
			m_vecTimeNodesLeaveFlag.push_back(false);
		}
		//Start Pop CMD Queue Thread...
		m_thread = new std::thread(std::bind(&TimeLine::DoPopCMD, this));
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

	void TimeLine::UnSetTimeNodeStayTimeout(size_t In_NodeIndex)
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		m_mapTimeNodeLeaveMode.erase(In_NodeIndex);
	}

	void TimeLine::PushCMD(CMDTYPE In_CMD)
	{
		std::lock_guard<std::mutex> autolock(m_mutex);
		m_queNODECMD.push(In_CMD);
		m_cvPop.notify_one();
	}

	void TimeLine::Enter()
	{
		std::unique_lock<std::mutex> unilck(m_mutex);
		if (m_bEnter == false && !m_bLeave && m_vecTimeNodes.size())
		{
			m_bEnter = true;
			GotoNode(unilck, 0);//First Node...
		}
	}

	void TimeLine::Next()
	{
		std::unique_lock<std::mutex> unilck(m_mutex);
		if (m_bEnter && !m_bLeave)
		{
			auto NextNodeIndex = m_stayTimePointIndex + 1;
			if (NextNodeIndex == GetTimeNodeNums())// Final Node...
				DoLeave();
			else
			{
				GotoNode(unilck, NextNodeIndex);//Next Node...
			}
		}
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
		CMDTYPE CMD;
		auto CalLeavems = [&](long long In_Stayms, long long In_Leavems)
		{
			return  (In_Stayms >= In_Leavems) && (m_vecTimeNodes[m_stayTimePointIndex].GetSate() != TimeNode::Hanging);
		};

		auto timeoutpredc = [&](long long In_Leavems)
		{
			//重新計算一次判斷停留時間是否已滿足條件
			m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = CalLeavems(m_vecTimeNodes[m_stayTimePointIndex].GetStayDurationMs(), In_Leavems);
			return m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] || m_bLeave;
		};

		auto defaultpredc = [&]
		{
			long long Leavems(0);
			return (!m_queNODECMD.empty() ||
					GetTimeNodeStayTimeout(m_stayTimePointIndex, Leavems) && Leavems/*在進行wait時, 如果因為m_stayTimePointIndex更改後被Notify, 檢查是否有timeout, 有就強制離開*/ ||
					m_bLeave);
		};

		// Start Run DoPopCMD....
		while (!m_bLeave)
		{
			std::unique_lock<std::mutex> unilck(m_mutex);
			if (!m_queNODECMD.empty())
			{
				CMD = m_queNODECMD.front();
				m_queNODECMD.pop();
				switch (CMD)
				{
				case CMDTYPE::GoNext:
					m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = true;
					break;

				case CMDTYPE::Hang:
					m_vecTimeNodes[m_stayTimePointIndex].Hang(true);
					break;

				case CMDTYPE::Keep:
					m_vecTimeNodes[m_stayTimePointIndex].Hang(false);
					break;
				}
				m_cvNext.notify_one();//叫醒Block住的Client Function
			}
			else
			{
				long long Leavems(0);
				//Check時間節點的條件
				if (GetTimeNodeStayTimeout(m_stayTimePointIndex, Leavems) && Leavems)
				{
					const auto& stayms = m_vecTimeNodes[m_stayTimePointIndex].GetStayDurationMs();

					if (CalLeavems(stayms, Leavems) && !m_vecTimeNodesLeaveFlag[m_stayTimePointIndex])//計算判斷停留時間是否已滿足條件
						m_vecTimeNodesLeaveFlag[m_stayTimePointIndex] = true;
					else
					{
						if (Leavems > stayms)//停留時間還不夠
							m_cvPop.wait_for(unilck, std::chrono::milliseconds(Leavems - stayms), std::bind(timeoutpredc, Leavems));//計算時間差值直接wait
						else
							m_cvPop.wait(unilck, defaultpredc);//時間條件已符合才會跑到這, 代表已離開這個節點或是剛好被Hang住
					}

					m_cvNext.notify_one();//叫醒Block住的Client Function
				}
				else
					m_cvPop.wait(unilck, defaultpredc);//若是無Timeout的Node跟一開始沒事做時卡在這
			}//end if (!m_queNODECMD.empty())
		}
	}

	void TimeLine::GotoNode(std::unique_lock<std::mutex> &unilck, size_t Index)
	{
		if ((m_vecTimeNodes[Index].GetSate() == TimeNode::None) &&
			(Index == 0 || (m_vecTimeNodes[Index - 1].GetSate() == TimeNode::Passed)))//確認已離開前一個節點
		{
			//Enter...
			m_vecTimeNodes[Index].Enter();
			m_stayTimePointIndex = Index;//Move~~

			m_cvPop.notify_one();
			long long Out_ms;
			const auto &iter = m_mapTimeNodeLeaveMode.find(Index);
			if (GetTimeNodeStayTimeout(Index, Out_ms))
			{
				//加入Hanging的判斷式是怕有先下了Hang CMD後沒下Kepp就直接下了GoNext
				m_cvNext.wait(unilck, [&] { return ((m_vecTimeNodesLeaveFlag[Index] && m_vecTimeNodes[m_stayTimePointIndex].GetSate() == TimeNode::Staying) || m_bLeave); });
			}
			//Leave...
			m_vecTimeNodes[Index].Leave();
		}
	}

	void TimeLine::DoLeave()
	{
		m_bLeave = true;
		m_cvPop.notify_one();
		m_cvNext.notify_all();
	}
}