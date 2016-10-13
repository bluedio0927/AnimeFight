#pragma once
#include "../Item/Item.h"
#include "../Card/CardStack.h"
#include "../Card/CardZone.h"

namespace AnimeFight
{
	namespace Core
	{
		class GameCore : public Item
		{
		public:
			GameCore(CardItem::CardStack *pStack, CardItem::CardZone *pZone1, CardItem::CardZone *pZone2, CardItem::CardZone *pZone3)
				:Item(ItemType::System),
				pSummonStack(pStack), pSummonZone(pZone1), pSakuraZone(pZone2), pVoidZone(pZone3), Round(0)
			{
				pSummonStack->ChangeOwner(this);
				pSakuraZone->ChangeOwner(this);
				pSakuraZone->ChangeOwner(this);
				pVoidZone->ChangeOwner(this);
			}
			
			virtual ~GameCore()
			{}

			const size_t& GetRound()
			{
				return Round;
			}

			void NextRound()
			{
				++Round;
			}

			CardItem::CardStack& SummonStack()
			{
				return *pSummonStack;
			}

			CardItem::CardZone& SummonZone()
			{
				return *pSummonZone;
			}

			CardItem::CardZone& SakuraZone()
			{
				return *pSakuraZone;
			}

			CardItem::CardZone& VoidZone()
			{
				return *pVoidZone;
			}

			size_t Summon(size_t uiNums = 1)
			{
				return pSummonStack->Deal(pSummonZone, uiNums);
			}

		private:
			CardItem::CardStack *pSummonStack;
			CardItem::CardZone *pSummonZone;
			CardItem::CardZone *pSakuraZone;
			CardItem::CardZone *pVoidZone;
			size_t Round;
		};
	}
}