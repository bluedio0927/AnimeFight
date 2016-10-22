#pragma once

#include "Character.h"
#include <deque>

namespace AnimeFight
{
	namespace TeamItem
	{
		class BasicTeam :public Item
		{
		public:
			BasicTeam(Item *pOwwner)
				:Item(ItemType::Team, pOwwner, L"隊伍區", L"儲存隊伍所有資源")
			{}

			virtual ~BasicTeam()
			{}

			const size_t GetTeamCharacters()
			{
				return m_deqChar.size();
			}

			CharacterItem::BasicCharacterItem *const Characters(size_t Index)
			{
				if (Index < m_deqChar.size())
					return m_deqChar[Index];
				else
					return nullptr;
			}

		protected:
			virtual bool SelfDoCanAppend(const Item *In_pAdjunctItem)
			{
				auto pChar = dynamic_cast<const CharacterItem::BasicCharacterItem *>(In_pAdjunctItem);
				if (pChar)
					return true;
				else
					return false;
			}

			virtual void AdjunctJoin(Item *pItem) override
			{
				auto pChar = dynamic_cast<CharacterItem::BasicCharacterItem *>(pItem);
				if (pChar)
				{
					const auto &iter = std::find(m_deqChar.begin(), m_deqChar.end(), pChar);
					if (iter == m_deqChar.end())
						m_deqChar.push_back(pChar);
				}
			}

			virtual void AdjunctLeave(Item *pItem)override
			{
				auto pChar = dynamic_cast<CharacterItem::BasicCharacterItem *>(pItem);
				if (pChar)
				{
					const auto &iter = std::find(m_deqChar.begin(), m_deqChar.end(), pChar);
					if (iter != m_deqChar.end())
						m_deqChar.erase(iter);
				}
			}
		private:
			std::deque<CharacterItem::BasicCharacterItem *> m_deqChar;
		};
	}
}