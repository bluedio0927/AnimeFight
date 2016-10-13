#pragma once
#include "CardStack.h"
#include "SpecialCard.h"
#include "TreasureCard.h"

namespace AnimeFight
{
	namespace CardItem
	{
		class SummonStack : public CardStack
		{
		public:
			SummonStack(Item *In_Ownen = nullptr, size_t rates = 1)
				:CardStack(CardStack::SummonStack, In_Ownen, L"召喚牌庫", L"儲存所有未被召喚的寶具牌的地方")
			{
				for (size_t i = 0; i < rates; ++i)
				{
					for (size_t j = 0; j < 4; ++j)
						operator<<(new MoonTimerCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new SevenColorBookCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new FantasySwordCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new WatchSwordCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new MagicGlassCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new MercurySwordCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new NightmareBellCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new OriginMagicBulletCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new SimulateNerveCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new GourdCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new MiniEightTrigramsCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new EmptyMoneyBoxCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new HolyBoneClothCard);
					
					for (size_t j = 0; j < 2; ++j)
						operator<<(new IdealTownshipCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new BlackKeyCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new MechanicalEmeraldCard);

					for (size_t j = 0; j < 1; ++j)
						operator<<(new SkyDreamCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new NightWordCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new AirMagicRollCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new VoidRuleCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new DefenseStickCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new CatRocketCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new BalanceOrbCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new ExRedRibbonCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new OfficialBookCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new FireWheelCard);

					for (size_t j = 0; j < 3; ++j)
						operator<<(new LemiMagestyCard);

					for (size_t j = 0; j < 2; ++j)
						operator<<(new RoyalHandCard);

					for (size_t j = 0; j < 4; ++j)
						operator<<(new CenturyLegendCard);
				}//END for (size_t i = 0; i < rates; ++i)

				Shuffle();
			}

			~SummonStack() {}
		};

		class HandStack : public CardStack
		{
		public:
			HandStack(Item *In_Ownen = nullptr)
				:CardStack(CardStack::HandStack, In_Ownen, L"牌庫", L"儲存所有可用的被召喚寶具牌的地方")
			{
				for (int i = 0; i < 7; ++i)
					operator<<(new BasicTicketCard);
				for (int i = 0; i < 3; ++i)
					operator<<(new BasicMagicCard);
				Shuffle();
			}
			~HandStack() {}
		};
	}
}