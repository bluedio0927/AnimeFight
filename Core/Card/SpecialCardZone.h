#pragma once
#include "CardZone.h"
#include "SpecialCard.h"

namespace AnimeFight
{
	namespace CardItem
	{
		class HandCardZone :public CardZone
		{
		public:
			HandCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::HandCardZone, pOwen, L"��P��", L"�x�s���a�Ҧ��i�Ϊ���P")
			{}
			~HandCardZone() {}
		};

		class CampCardZone :public CardZone
		{
		public:
			CampCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::CampCardZone, pOwen, L"�}�a��", L"�x�s���a�Ҧ����X����P")
			{}
			~CampCardZone() {}
		};

		class DiscarCardZone :public CardZone
		{
		public:
			DiscarCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::DiscarCardZone, pOwen, L"��P��", L"�x�s���a�Ҧ��ϥιL�᪺��P")
			{}
			~DiscarCardZone() {}
		};

		class SakuraCookieZone :public CardZone
		{
		public:
			SakuraCookieZone(Item *pOwen = nullptr, size_t rates = 1)
				:CardZone(CardZone::SakuraCookieZone, pOwen, L"����P��", L"�x�s�Ҧ����l�ꪺ����")
			{
				for (size_t i = 0; i < rates; ++i)
				{
					for (size_t j = 0; j < 15; ++j)
						operator<<(new SakuraCookieCard);
				}
			}
			~SakuraCookieZone() {}
		};

		class VoidCardZone :public CardZone
		{
		public:
			VoidCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::VoidCardZone, pOwen, L"���ذ�", L"�x�s�Ҧ��Q��v���P")
			{}
			~VoidCardZone() {}
		};

		class SummonCardZone :public CardZone
		{
		public:
			SummonCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::VoidCardZone, pOwen, L"�l���", L"�x�s�Ҧ��Q�l��X���_��P")
			{}
			~SummonCardZone() {}
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