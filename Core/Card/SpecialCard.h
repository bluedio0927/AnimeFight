#pragma once
#include "Card.h"

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
		};

		class BasicMagicCard : public BasicCard
		{
		public:
			BasicMagicCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::BasicMagic, 0, 2, 2, 1, 0, In_Ownen)
			{}
		};

		class SakuraCookieCard : public BasicCard
		{
		public:
			SakuraCookieCard(Item *In_Ownen = nullptr)
				:BasicCard(CardType::SakuraCookie, 3, 3, 3, 1, 2, In_Ownen)
			{}
		};
	}
}