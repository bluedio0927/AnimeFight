#pragma once
#include "Card.h"
#include "../Character/Character.h"
namespace AnimeFight
{
	namespace CardItem
	{
		class BasicTicketCard : public BasicCard
		{
		public:
			BasicTicketCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::BasicTicket, 0, 2, 2, 0, 1, In_Ownen)
			{}
			~BasicTicketCard() {}
		};

		class BasicMagicCard : public BasicCard
		{
		public:
			BasicMagicCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::BasicMagic, 0, 2, 2, 1, 0, In_Ownen)
			{}
			~BasicMagicCard() {}
		};

		class SakuraCookieCard : public BasicCard
		{
		public:
			SakuraCookieCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::SakuraCookie, 3, 3, 3, 1, 2, In_Ownen)
			{}
			~SakuraCookieCard() {}
			virtual bool operator()(long long Reserved, Item *pOwner, std::vector<Item *> *pVecItem) override
			{
				if (Reserved == Post)
				{
					if (pOwner && pOwner->GetType() == ItemType::Character)
					{
						auto pCharacter = dynamic_cast<CharacterItem::BasicCharacterItem *>(pOwner);
						pCharacter->addSkillpoint(1);
					}
					return true;
				}
				else
					return false;
			}
		};
	}
}