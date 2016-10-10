#pragma once

namespace AnimeFight
{
	namespace CharacterItem
	{
		enum CharacterType
		{
			RyougiShiki//兩儀式
		};

		enum CharacterRace
		{
			Human,
			NonHuman,
			Chaos
		};

		using wspair = std::pair<std::wstring, std::wstring>;
		static std::map<CharacterType, wspair> gs_mapCharacterItemString;

		bool CharacterInit()
		{
			gs_mapCharacterItemString[RyougiShiki] = std::make_pair(L"兩儀式", L"直死之魔眼");
			return true;
		}

		static bool CharacterInited = CharacterInit();
	}
}