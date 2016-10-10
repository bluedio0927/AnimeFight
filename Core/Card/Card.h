#pragma once
#include "../Item/Item.h"
#include "CardDefine.h"
namespace AnimeFight
{
	namespace CardItem
	{
		class BasicCard : public Item
		{
		public:
			//Type, Cost, SpellsDef, Phydefs, Magic, Souls, ItemOwner, ItemName, ItemDescript
			BasicCard(CardType In_eType, int In_Cost, int In_SpellsDef, int In_Phydefs, int In_Magic, int In_Souls, Item *pOwnen = nullptr)
				:Item(ItemType::Card, pOwnen, gs_mapCardItemString[In_eType].first, gs_mapCardItemString[In_eType].second)
				, m_eType(In_eType), m_iCost(In_Cost)
				, m_iSpellsDef(In_SpellsDef), m_iPhyDef(In_Phydefs)
				, m_iMagic(In_Magic), m_iSoul(In_Souls)
			{}

			virtual ~BasicCard()
			{}

			const CardType& GetCardType()
			{
				return m_eType;
			}

			int GetCost()
			{
				return m_iCost + ExtendGetCost();
			}

			int GetSpellsDefence()
			{
				return m_iSpellsDef + ExtendGetSpellsDefence();
			}

			int GetPhysicsDefence()
			{
				return m_iPhyDef + ExtendGetPhysicsDefence();
			}

			int GetMagic()
			{
				return m_iMagic + ExtendGetMagic();
			}

			int GetSoul()
			{
				return m_iSoul + ExtendGetSoul();
			}

		protected:

			virtual int ExtendGetCost()
			{
				return 0;
			}

			virtual int ExtendGetSpellsDefence()
			{
				return 0;
			}

			virtual int ExtendGetPhysicsDefence()
			{
				return 0;
			}

			virtual int ExtendGetMagic()
			{
				return 0;
			}

			virtual int ExtendGetSoul()
			{
				return 0;
			}
		private:
			CardType m_eType;
			int m_iCost;
			int m_iSpellsDef, m_iPhyDef;
			int m_iMagic, m_iSoul;
		};
	}
}