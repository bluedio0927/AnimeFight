#include "TimeNode.h"

namespace AnimeFight
{
	TimeNode::TimeNode(long long In_lNumber)
		:m_lNumber(In_lNumber), m_NodeState(None), m_stayms(std::chrono::milliseconds(0))
	{}

	TimeNode::~TimeNode()
	{}

	const long long& TimeNode::GetNumber()
	{
		return m_lNumber;
	}

	const TimeNode::NodeState& TimeNode::GetSate()
	{
		return m_NodeState;
	}

	bool TimeNode::Enter()
	{
		if (m_NodeState == None)
		{
			m_EnterTp = mHangTp = TimeType::now();
			m_NodeState = Staying;
			return true;
		}
		else
			return false;
	}

	bool TimeNode::Hang(bool bEnable)
	{
		bool bRet(false);
		if (bEnable && m_NodeState == Staying)
		{
			UpdateStayMs();
			m_NodeState = Hanging;
			bRet = true;
		}
		else if (!bEnable && m_NodeState == Hanging)
		{
			mHangTp = TimeType::now();
			m_NodeState = Staying;
			bRet = true;
		}
		
		return bRet;
	}

	bool TimeNode::Leave()
	{
		if (m_NodeState == Staying)
		{
			UpdateStayMs();
			m_LeaveTp = mHangTp;
			m_NodeState = Passed;
			return true;
		}
		else
			return false;
	}

	long long TimeNode::GetStayDurationMs()
	{
		if (m_NodeState == Staying)
			UpdateStayMs();

		return m_stayms.count();
	}

	bool TimeNode::GetEnterTimePoint(TimeType::time_point &Out_Point)
	{
		if (m_NodeState != None)
		{
			Out_Point = m_EnterTp;
			return true;
		}
		else
			return false;
	}

	bool TimeNode::GetLeaveTimePoint(TimeType::time_point &Out_Point)
	{
		if (m_NodeState == Passed)
		{
			Out_Point = m_LeaveTp;
			return true;
		}
		else
			return false;
	}

	void TimeNode::UpdateStayMs()
	{
		const auto &tpNow = TimeType::now();
		m_stayms += std::chrono::duration_cast<std::chrono::milliseconds>(tpNow - mHangTp);
		mHangTp = TimeType::now();
	}
}