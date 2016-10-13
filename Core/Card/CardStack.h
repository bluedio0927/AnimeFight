#pragma once
#include <deque>
#include <algorithm>
#include <chrono>
#include "Card.h"

namespace AnimeFight
{
	namespace CardItem
	{
		class CardStack : public Item
		{
		public:
			enum StackType
			{
				HandStack,
				SummonStack
			};

			template<typename ...Args>
			CardStack(StackType In_eType, Args&& ...args)
				:Item(ItemType::CardStack, std::forward<Args>(args)...)
				, m_eType(In_eType)
			{}

			virtual ~CardStack()
			{}

			//取得牌堆的屬性
			const StackType& GetStackType()
			{
				return m_eType;
			}

			//發牌堆中最上面的一張牌給其他牌區
			size_t Deal(Item *pItem, size_t In_Nums = 1)
			{
				size_t Deals(0);
				if (pItem->GetType() == ItemType::CardZone)
				{
					auto itercard = m_deqCardStack.begin();
					while (In_Nums && itercard != m_deqCardStack.end())
					{
						if (*(*itercard) >> (*pItem))
						{
							//不做pop front的原因是牌移轉出去後, Item會呼叫AdjunctLeave
							++Deals;
							--In_Nums;
							itercard = m_deqCardStack.begin();
						}
						else
							break;//不可以被附屬為牌區到達上限, 直接離開
					}
				}
				return Deals;
			}

			//取得牌堆的牌數
			size_t GetCardNums()
			{
				return m_deqCardStack.size();
			}

			//洗牌
			void Shuffle()
			{
				using namespace std::chrono;
				std::srand((unsigned int)system_clock::to_time_t(system_clock::now()));
				std::random_shuffle(m_deqCardStack.begin(), m_deqCardStack.end());
			}

		protected:
			virtual void AdjunctJoin(Item *pItem) override
			{
				auto pCard = dynamic_cast<BasicCard *>(pItem);
				if (pCard)
					m_deqCardStack.push_front(pCard);
			}

			virtual void AdjunctLeave(Item *pItem)override
			{
				auto pCard = dynamic_cast<BasicCard *>(pItem);
				if (pCard)
				{
					auto iter = std::find(m_deqCardStack.begin(), m_deqCardStack.end(), pCard);
					if (iter != m_deqCardStack.end())
						m_deqCardStack.erase(iter);
				}
			}

		private:
			StackType m_eType;
			std::deque<BasicCard *> m_deqCardStack;
		};
	}
}