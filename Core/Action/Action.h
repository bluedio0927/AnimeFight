#pragma once

#include "../Time/TimeLine.h"
#include "../Item/Item.h"
#include "../../Common/3rdParty/QB/Event/Event.h"

#include <list>
#include <functional>

namespace AnimeFight
{
	class Action
	{
	public:
		using ActionHandle = std::function<void(int iActionID, Item* Initiator, Item* Target)>;
		using ActionEvent = QB::Event<ActionHandle>;
		using ActionResponser = ActionEvent::Listener;

	public:
		Action(int In_ID, size_t ActionStage, Item* Initiator);

		const int& GetActionID();

		bool addTarget(Item *In_Target);

		bool removeTarget(Item *In_Target);

		bool addResponser(size_t Index, ActionResponser& In_Responser);

		bool removeResponser(size_t Index, ActionResponser& In_Responser);

		void SetReady();

		void SendStageCMD(TimeLine::CMDTYPE CMD);

		TimeLine::NodeState DoNextStage();

		void Cancel();

		bool IsFinished();

	private:
		int			m_ActionID;
		TimeLine	m_TimeLine;
		size_t		m_nowStage;
		Item*		m_Initiator;//Action的發起者
		std::vector<ActionEvent>	m_vecActionEvent;
		std::map<size_t, Item *>	m_mapTargets;//Action作用的目標
	};
};