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
			BasicCharacterItem(CharacterType In_eCtype, CharacterRace In_eRace, 
				CardItem::CardStack *pHandStack, CardItem::CardZone *pHandCardZone, CardItem::CardZone *pCampCardZone, CardItem::CardZone *pDiscarCardZone, CardItem::CardZone *pVoidCardZone,
				Item* In_pOwner)
				:Item(ItemType::Character, In_pOwner, gs_mapCharacterItemString[In_eCtype].first, gs_mapCharacterItemString[In_eCtype].second)
				, m_eType(In_eCtype), m_eRace(m_eRace)
				, CampCardZone(pCampCardZone), DiscarCardZone(pDiscarCardZone), HandCardZone(pHandCardZone), HandStack(pHandStack), Ex_VoidCardZone(pVoidCardZone)
				, m_iSouls(0), m_iMagic(0), m_iSkillpoints(0), m_iHP(5)
			{
				CampCardZone->ChangeOwner(this);
				DiscarCardZone->ChangeOwner(this);
				HandCardZone->ChangeOwner(this);
				HandStack->ChangeOwner(this);
				HandStack->Deal(HandCardZone, 6);
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
				auto Cards = CampCardZone->GetAllCards();
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

			const int& GetSkillPoint()
			{
				return m_iSkillpoints;
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
					return (*pCard) >> DiscarCardZone;
				}
				else
					return false;
			}

			bool PostHandCard(CardItem::BasicCard *pCard)
			{
				auto iter = HandCardZone->Choose(pCard);
				if (HandCardZone->IsEffectiveTarget(iter))
				{
					bool bRet = HandCardZone->CardMove(iter, CampCardZone);
					if (bRet)//出牌成功立刻結算魔力
						m_iMagic += pCard->GetMagic();
					//觸發出牌效果
					(*pCard)(CardItem::Post, this, nullptr);
					return bRet;
				}
				else
					return false;
			}

			bool DiscardHandCard(CardItem::BasicCard *pCard)
			{
				auto iter = HandCardZone->Choose(pCard);
				if (HandCardZone->IsEffectiveTarget(iter))
					return HandCardZone->CardMove(iter, DiscarCardZone);
				else
					return false;
			}

			bool ExileHandCard(CardItem::BasicCard *pCard)
			{
				auto iter = HandCardZone->Choose(pCard);
				if (HandCardZone->IsEffectiveTarget(iter))
					return HandCardZone->CardMove(iter, Ex_VoidCardZone);
				else
					return false;
			}

			bool ExileDiscardCard(CardItem::BasicCard *pCard)
			{
				auto iter = DiscarCardZone->Choose(pCard);
				if (DiscarCardZone->IsEffectiveTarget(iter))
					return DiscarCardZone->CardMove(iter, Ex_VoidCardZone);
				else
					return false;
			}

			size_t GetHandCard(size_t CardNums)
			{
				return HandStack->Deal(HandCardZone, CardNums);
			}

			void addSkillpoint(int iSkills)
			{
				m_iSkillpoints += iSkills;
			}

			CardItem::CardZone *CampCardZone;
			CardItem::CardZone *DiscarCardZone;
			CardItem::CardZone *HandCardZone;
			CardItem::CardZone *Ex_VoidCardZone;
			CardItem::CardStack *HandStack;

		private:
			void CalCampOwnMagics()
			{
				m_iMagic = 0;
				auto Cards = CampCardZone->GetAllCards();
				for (auto &iter : Cards)
					m_iMagic += iter->GetCardType();
			}

		private:
			CharacterType m_eType;
			CharacterRace m_eRace;
			int	m_iSouls;
			int m_iMagic;
			int m_iSkillpoints;
			int m_iHP;
		};
	}
}