#pragma once
#include "Card.h"
#include "../Item/Item.h"
#include <deque>

namespace AnimeFight
{
	namespace CardItem
	{
		class CardZone:public Item
		{
		public:
			enum ZoneType
			{
				HandCardZone,
				SummonCardZone,
				SakuraCookieZone,
				CampCardZone,
				VoidCardZone,
				DiscarCardZone
			};
			
			using CardDeq = std::deque<BasicCard *>;
			using CardTarget = CardDeq::iterator;

			template<typename ...Args>
			CardZone(ZoneType In_eType, Args&& ...args)
				:Item(ItemType::CardZone, std::forward<Args>(args)...)
				, m_eType(In_eType)
			{}

			virtual ~CardZone() {}

			//���o�P�Ϫ��ݩ�
			const ZoneType& GetZoneType()
			{
				return m_eType;
			}

			size_t GetAllCardNums()
			{
				return m_deqCardZone.size();
			}

			//���o�P�ϥثe�Ҧ����P
			const CardDeq& GetAllCards()
			{
				return m_deqCardZone;
			}

			//��ܨ䤤�@�i
			CardTarget Choose(BasicCard *pCard)
			{
				return std::find(m_deqCardZone.begin(), m_deqCardZone.end(), pCard);
			}

			//�P�_����ܪ��P�O�_����
			bool IsEffectiveTarget(CardTarget &Target)
			{
				return  Target != m_deqCardZone.end();
			}

			//�N�P���ʨ��L�P�ϩεP�w
			bool CardMove(CardTarget &cardtarget, Item* pTarget)
			{
				if (IsEffectiveTarget(cardtarget) &&
					pTarget->GetType() == ItemType::CardStack || pTarget->GetType() == ItemType::CardZone)
					return *(*cardtarget) >> pTarget;//����pop front����]�O�P����X�h��, Item�|�I�sAdjunctLeave
				else
					return false;
			}

			bool CardAllMove(Item* pTarget)
			{
				if (pTarget->GetType() == ItemType::CardStack || pTarget->GetType() == ItemType::CardZone)
				{
					auto iter = m_deqCardZone.begin();
					while (iter != m_deqCardZone.end())
					{
						if (*(*iter) >> pTarget)//����pop front����]�O�P����X�h��, Item�|�I�sAdjunctLeave
							iter = m_deqCardZone.begin();
						else
							++iter;
					}
					return true;
				}
				else
					return false;
			}

		protected:
			virtual void AdjunctJoin(Item *pItem) override
			{
				auto pCard = dynamic_cast<BasicCard *>(pItem);
				if (pCard)
					m_deqCardZone.push_front(pCard);
			}

			virtual void AdjunctLeave(Item *pItem)override
			{
				auto pCard = dynamic_cast<BasicCard *>(pItem);
				if (pCard)
					m_deqCardZone.erase(Choose(pCard));
			}
		private:
			ZoneType m_eType;
			CardDeq m_deqCardZone;
		};
	}
}