#pragma once
#include "Character.h"
#include "../Card/SpecialCardStack.h"
#include "../Card/SpecialCardZone.h"
#include "../System/GameCore.h"
namespace AnimeFight
{
	namespace CharacterItem
	{
		static BasicCharacterItem* CreateCharacter(CharacterType In_eCtype, CharacterRace In_eRace, Core::GameCore* In_pOwner)
		{
			return new BasicCharacterItem(In_eCtype, In_eRace, 
				new CardItem::HandStack, new CardItem::HandCardZone, new CardItem::CampCardZone, new CardItem::DiscarCardZone, &In_pOwner->VoidZone(), In_pOwner);
		}
	}
}