#include "Action.h"

namespace AnimeFight
{
	Action::Action(int In_ID, size_t ActionStage, Item* Initiator)
		:m_ActionID(In_ID), m_TimeLine(ActionStage), m_Initiator(Initiator)
		, m_vecActionEvent(ActionStage + 1), m_nowStage(0)
	{
	}

	const int& Action::GetActionID()
	{
		return m_ActionID;
	}

	bool Action::SetStageTimeout(size_t In_NodeIndex, long long In_Timeoutms)
	{
		return m_TimeLine.SetTimeNodeStayTimeout(In_NodeIndex, In_Timeoutms);
	}

	bool Action::UnSetStageTimeout(size_t In_NodeIndex)
	{
		return m_TimeLine.UnSetTimeNodeStayTimeout(In_NodeIndex);
	}

	bool Action::addTarget(Item *In_Target)
	{
		auto sIndex = (size_t)In_Target;
		if (m_mapTargets.find(sIndex) == m_mapTargets.end())
		{
			m_mapTargets[sIndex] = In_Target;
			return true;
		}
		else
			return false;
	}

	bool Action::removeTarget(Item *In_Target)
	{
		auto sIndex = (size_t)In_Target;
		if (m_mapTargets.find(sIndex) != m_mapTargets.end())
		{
			m_mapTargets.erase(sIndex);
			return true;
		}
		else
			return false;
	}

	bool Action::addResponser(size_t Index, ActionResponser& In_Responser)
	{
		if (Index < m_vecActionEvent.size())
			return m_vecActionEvent[Index] += In_Responser;
		else
			return false;
	}

	bool Action::removeResponser(size_t Index, ActionResponser& In_Responser)
	{
		if (Index < m_vecActionEvent.size())
			return m_vecActionEvent[Index] -= In_Responser;
		else
			return false;
	}

	void Action::SetReady()
	{
		m_TimeLine.Enter();
	}

	void Action::Cancel()
	{
		m_TimeLine.Cancel();
	}

	bool Action::IsFinished()
	{
		return m_TimeLine.IsEnd();
	}

	size_t Action::GetNowStage()
	{
		return m_nowStage;
	}

	TimeLine::NodeState Action::DoNextStage()
	{
		m_nowStage = m_TimeLine.GetNowStayPointIndex()+1;
		//觸發所有註冊的響應
		for(auto &iter : m_mapTargets)
			m_vecActionEvent[m_nowStage].Invoke(m_ActionID, m_Initiator, iter.second);
		return m_TimeLine.Next();
	}

	void Action::SendStageCMD(TimeLine::CMDTYPE CMD)
	{
		m_TimeLine.PushCMD(CMD);
	}
}