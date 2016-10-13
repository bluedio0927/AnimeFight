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
				:CardZone(CardZone::HandCardZone, pOwen, L"手牌區", L"儲存玩家所有可用的手牌")
			{}
			~HandCardZone() {}
		};

		class CampCardZone :public CardZone
		{
		public:
			CampCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::CampCardZone, pOwen, L"陣地區", L"儲存玩家所有打出的手牌")
			{}
			~CampCardZone() {}
		};

		class DiscarCardZone :public CardZone
		{
		public:
			DiscarCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::DiscarCardZone, pOwen, L"棄牌區", L"儲存玩家所有使用過後的手牌")
			{}
			~DiscarCardZone() {}
		};

		class SakuraCookieZone :public CardZone
		{
		public:
			SakuraCookieZone(Item *pOwen = nullptr, size_t rates = 1)
				:CardZone(CardZone::SakuraCookieZone, pOwen, L"櫻花餅牌區", L"儲存所有未召喚的櫻花餅")
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
				:CardZone(CardZone::VoidCardZone, pOwen, L"間隙區", L"儲存所有被放逐的牌")
			{}
			~VoidCardZone() {}
		};

		class SummonCardZone :public CardZone
		{
		public:
			SummonCardZone(Item *pOwen = nullptr)
				:CardZone(CardZone::VoidCardZone, pOwen, L"召喚區", L"儲存所有被召喚出的寶具牌")
			{}
			~SummonCardZone() {}
			virtual bool SelfDoCanAppend(const Item *In_pAdjunctItem) override
			{
				//召喚牌區只能有6張
				if (GetMapAdjunctItew().size() >= 6)
					return false;
				else
					return true;
			}
		};
	}
}