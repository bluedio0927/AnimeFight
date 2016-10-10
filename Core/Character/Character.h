#pragma once
#include "../Item/Item.h"
#include "CharacterDefine.h"
#include "../Card/CardZone.h"
#include "../Card/CardStack.h"

namespace AnimeFight
{
	namespace CharacterItem
	{
		class BasicCharacterItem:public Item
		{
		public:
			BasicCharacterItem(CharacterType In_eCtype, CharacterRace In_eRace, Item* In_pOwner)
				:Item(ItemType::Character, In_pOwner, gs_mapCharacterItemString[In_eCtype].first, gs_mapCharacterItemString[In_eCtype].second)
				, m_eType(In_eCtype), m_eRace(m_eRace)
				, CampCardZone(this), DiscarCardZone(this), HandCardZone(this), HandStack(this), m_iSouls(0), m_iMagic(0), m_iSkillpoints(0)
			{
				HandStack.Deal(&HandCardZone, 6);
			}

			virtual ~BasicCharacterItem() {}

			const CharacterType& GetCharacterType()
			{
				return m_eType;
			}

			const CharacterRace& GetCharacterRace()
			{
				return m_eRace;
			}

			void ResetState()
			{
				CalCampOwnSouls();
				CalCampOwnMagics();
				m_iSkillpoints = 1;
			}

			void CalCampOwnSouls()
			{
				m_iSouls = 0;
				auto Cards = CampCardZone.GetAllCards();
				for (auto &iter : Cards)
					m_iSouls += iter->GetSoul();
			}

			const int& GetSouls()
			{
				return m_iSouls;
			}

			const int& GetMagics()
			{
				return m_iMagic;
			}

			//可以繼承覆寫, 有角色技能是會降低購買的Cost
			virtual int CalBuyCost(CardItem::BasicCard *pCard)
			{
				return pCard->GetCost();
			}

			bool CanBuyit(CardItem::BasicCard *pCard)
			{
				if (CalBuyCost(pCard) <= m_iSouls)
					return true;
				else
					return false;
			}

			bool Buyit(CardItem::BasicCard *pCard)
			{
				int iCost(CalBuyCost(pCard));
				if (iCost <= m_iSouls)
				{
					m_iSouls -= iCost;
					(*pCard) >> DiscarCardZone;
				}
				else
					return false;
			}

			bool PostHandCard(CardItem::BasicCard *pCard)
			{
				auto iter = HandCardZone.Choose(pCard);
				if (HandCardZone.IsEffectiveTarget(iter))
				{
					bool bRet = HandCardZone.CardMove(iter, &CampCardZone);
					if (bRet)//出牌成功立刻結算魔力
						m_iMagic += pCard->GetMagic();
					return bRet;
				}
				else
					return false;
			}

			CardItem::CampCardZone CampCardZone;
			CardItem::DiscarCardZone DiscarCardZone;
			CardItem::HandCardZone HandCardZone;
			CardItem::HandStack HandStack;

		private:
			void CalCampOwnMagics()
			{
				m_iMagic = 0;
				auto Cards = CampCardZone.GetAllCards();
				for (auto &iter : Cards)
					m_iMagic += iter->GetCardType();
			}

		private:
			CharacterType m_eType;
			CharacterRace m_eRace;
			int	m_iSouls;
			int m_iMagic;
			int m_iSkillpoints;
		};
	}
}