#pragma once

namespace AnimeFight
{
	namespace CharacterItem
	{
		enum CharacterType
		{
			RyougiShiki//�����
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
			gs_mapCharacterItemString[RyougiShiki] = std::make_pair(L"�����", L"�������]��");
			return true;
		}

		static bool CharacterInited = CharacterInit();
	}
}