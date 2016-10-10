#pragma once
#include "Card.h"
#include "SpecialCard.h"
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

		class HandCardZone :public CardZone
		{
		public:
			HandCardZone(Item *pOwen)
				:CardZone(CardZone::HandCardZone, pOwen, L"��P��", L"�x�s���a�Ҧ��i�Ϊ���P")
			{}
		};

		class CampCardZone :public CardZone
		{
		public:
			CampCardZone(Item *pOwen)
				:CardZone(CardZone::CampCardZone, pOwen, L"�}�a��", L"�x�s���a�Ҧ����X����P")
			{}
		};

		class DiscarCardZone :public CardZone
		{
		public:
			DiscarCardZone(Item *pOwen)
				:CardZone(CardZone::DiscarCardZone, pOwen, L"��P��", L"�x�s���a�Ҧ��ϥιL�᪺��P")
			{}
		};

		class SakuraCookieZone :public CardZone
		{
		public:
			SakuraCookieZone(Item *pOwen, size_t rates = 1)
				:CardZone(CardZone::SakuraCookieZone, pOwen, L"����P��", L"�x�s�Ҧ����l�ꪺ����")
			{
				for (size_t i = 0; i < rates; ++i)
				{
					for (size_t j = 0; j < 20; ++j)
						operator<<(new SakuraCookieCard);
				}
			}
		};

		class VoidCardZone :public CardZone
		{
		public:
			VoidCardZone(Item *pOwen)
				:CardZone(CardZone::VoidCardZone, pOwen, L"���ذ�", L"�x�s�Ҧ��Q��v���P")
			{}
		};

		class SummonCardZone :public CardZone
		{
		public:
			SummonCardZone(Item *pOwen)
				:CardZone(CardZone::VoidCardZone, pOwen, L"�l���", L"�x�s�Ҧ��Q�l��X���_��P")
			{}

			virtual bool SelfDoCanAppend(const Item *In_pAdjunctItem) override
			{
				//�l��P�ϥu�঳6�i
				if (GetMapAdjunctItew().size() >= 6)
					return false;
				else
					return true;
			}
		};
	}
}