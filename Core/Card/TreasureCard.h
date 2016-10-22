#pragma once
#include "Card.h"
#include "../Character/Character.h"
#include "../System/GameCore.h"
namespace AnimeFight
{
	namespace CardItem
	{
		class MoonTimerCard : public BasicCard
		{
		public:
			MoonTimerCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::MoonTimer, 3, 2, 2, 1, 1, In_Ownen)
			{}

			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (Reserved == Post)
				{
					if (pOwner && pOwner->GetType() == ItemType::Character)
					{
						auto pCharacter = dynamic_cast<CharacterItem::BasicCharacterItem *>(pOwner);
						pCharacter->GetHandCard(1);
					}
					return true;
				}
				else
					return false;
			}
		};

		class SevenColorBookCard : public BasicCard
		{
		public:
			SevenColorBookCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::SevenColorBook, 5, 4, 0, 2, 1, In_Ownen)
			{}
		};

		class FantasySwordCard : public BasicCard
		{
		public:
			FantasySwordCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::FantasySword, 6, 0, 4, 2, 2, In_Ownen)
			{}
		};

		class WatchSwordCard : public BasicCard
		{
		public:
			WatchSwordCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::WatchSword, 6, 0, 4, 1, 1, In_Ownen)
			{}
		};

		class MagicGlassCard : public BasicCard
		{
		public:
			MagicGlassCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::MagicGlass, 5, 5, 0, 0, 1, In_Ownen)
			{}
		};

		class MercurySwordCard : public BasicCard
		{
		public:
			MercurySwordCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::MercurySword, 3, 1, 1, 4, 1, In_Ownen)
			{}
		};

		class NightmareBellCard : public BasicCard
		{
		public:
			NightmareBellCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::NightmareBell, 3, 2, 2, 0, 1, In_Ownen)
			{}
		};

		class OriginMagicBulletCard : public BasicCard
		{
		public:
			OriginMagicBulletCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::OriginMagicBullet, 3, 2, 2, 0, 0, In_Ownen)
			{}
		};

		class SimulateNerveCard : public BasicCard
		{
		public:
			SimulateNerveCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::SimulateNerve, 4, 0, 4, 0, 2, In_Ownen)
			{}
		};

		class GourdCard : public BasicCard
		{
		public:
			GourdCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::Gourd, 6, 3, 3, 4, 1, In_Ownen)
			{}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (!pOwner)
					return false;

				if (Reserved == Come)
				{
					auto pCore = dynamic_cast<Core::GameCore *>(pOwner->GetSupenOwner());
					for (size_t i = 0; i < pCore->RedTeam().GetTeamCharacters(); ++i)
						pCore->RedTeam().Characters(i)->GetHandCard(1);
					for (size_t i = 0; i < pCore->BlueTeam().GetTeamCharacters(); ++i)
						pCore->BlueTeam().Characters(i)->GetHandCard(1);
					return true;
				}
				else
					return false;
			}
		};

		class MiniEightTrigramsCard : public BasicCard
		{
		public:
			MiniEightTrigramsCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::MiniEightTrigrams, 7, 4, 0, 4, 0, In_Ownen)
			{}
		};

		class EmptyMoneyBoxCard : public BasicCard
		{
		public:
			EmptyMoneyBoxCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::EmptyMoneyBox, 6, 3, 3, 0, 0, In_Ownen)
			{}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (!pOwner)
					return false;
				if (Reserved == Post)
				{
					if (pOwner && pOwner->GetType() == ItemType::Character)
					{
						auto pCharacter = dynamic_cast<CharacterItem::BasicCharacterItem *>(pOwner);
						pCharacter->GetHandCard(2);
					}
					return true;
				}
				else
					return false;
			}
		};

		class HolyBoneClothCard : public BasicCard
		{
		public:
			HolyBoneClothCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::HolyBoneCloth, 5, 4, 0, 1, 1, In_Ownen)
			{}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				return false;
			}
		};

		class IdealTownshipCard : public BasicCard
		{
		public:
			IdealTownshipCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::IdealTownship, 7, 7, 7, 3, 1, In_Ownen)
			{}
		};

		class BlackKeyCard : public BasicCard
		{
		public:
			BlackKeyCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::BlackKey, 3, 3, 3, 2, 0, In_Ownen)
			{}
		};

		class MechanicalEmeraldCard : public BasicCard
		{
		public:
			MechanicalEmeraldCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::MechanicalEmerald, 4, 3, 3, 0, 0, In_Ownen)
			{}
		};

		class SkyDreamCard : public BasicCard
		{
		public:
			SkyDreamCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::SkyDream, 9, 4, 4, 0, 0, In_Ownen)
			{}
		};

		class NightWordCard : public BasicCard
		{
		public:
			NightWordCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::NightWord, 4, 0, 5, 2, 1, In_Ownen)
			{}
		};

		class AirMagicRollCard : public BasicCard
		{
		public:
			AirMagicRollCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::AirMagicRoll, 4, 4, 0, 4, 0, In_Ownen)
			{}
		};

		class VoidRuleCard : public BasicCard
		{
		public:
			VoidRuleCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::VoidRule, 6, 5, 5, 0, 0, In_Ownen)
			{}
		};

		class DefenseStickCard : public BasicCard
		{
		public:
			DefenseStickCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::DefenseStick, 6, 0, 4, 2, 2, In_Ownen)
			{}
		};

		class CatRocketCard : public BasicCard
		{
		public:
			CatRocketCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::CatRocket, 4, 3, 3, 5, 2, In_Ownen)
			{}
		};

		class BalanceOrbCard : public BasicCard
		{
		public:
			BalanceOrbCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::BalanceOrb, 7, 4, 4, 2, 2, In_Ownen)
			{}
		};

		class ExRedRibbonCard : public BasicCard
		{
		public:
			ExRedRibbonCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::ExRedRibbon, 1, 3, 3, 2, 0, In_Ownen)
			{}
		};

		class OfficialBookCard : public BasicCard
		{
		public:
			OfficialBookCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::OfficialBook, 5, 4, 4, 2, 2, In_Ownen)
			{}
		};

		class FireWheelCard : public BasicCard
		{
		public:
			FireWheelCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::FireWheel, 5,3, 3, 3, 1, In_Ownen)
			{}
		};

		class LemiMagestyCard : public BasicCard
		{
		public:
			LemiMagestyCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::LemiMagesty, 4, 3, 3, 1, 1, In_Ownen)
			{}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (Reserved == Post)
				{
					if (pOwner && pOwner->GetType() == ItemType::Character)
					{
						auto pCharacter = dynamic_cast<CharacterItem::BasicCharacterItem *>(pOwner);
						pCharacter->GetHandCard(2);
					}
					return true;
				}
				else
					return false;
			}
		};

		class RoyalHandCard : public BasicCard
		{
		public:
			RoyalHandCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::RoyalHand, 5, 3, 3, 3, 1, In_Ownen)
			{}
		};

		class CenturyLegendCard : public BasicCard
		{
		public:
			CenturyLegendCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::CenturyLegend, 2, 0, 0, 1, 1, In_Ownen)
			{}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (!pOwner)
					return false;
				if (Reserved == Come)
				{
					auto pCore = dynamic_cast<Core::GameCore *>(pOwner->GetSupenOwner());
					for (size_t i = 0; i < pCore->RedTeam().GetTeamCharacters(); ++i)
						pCore->RedTeam().Characters(i)->GetHandCard(1);
					for (size_t i = 0; i < pCore->BlueTeam().GetTeamCharacters(); ++i)
						pCore->BlueTeam().Characters(i)->GetHandCard(1);
					return true;
				}
				else
					return false;
			}
		};
	}
}