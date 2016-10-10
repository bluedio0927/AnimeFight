#pragma once
#include <utility>
#include <map>
namespace AnimeFight
{
	namespace CardItem
	{
		enum CardType
		{
			BasicTicket = 0, BasicMagic, SakuraCookie, //SpeicalCard
			MoonTimer, SevenColorBook, FantasySword,
			WatchSword, MagicGlass, MercurySword,
			NightmareBell, OriginMagicBullet, SimulateNerve,
			Gourd, MiniEightTrigrams, EmptyMoneyBox,
			HolyBoneCloth, IdealTownship, BlackKey,
			MechanicalEmerald, SkyDream, NightWord,
			AirMagicRoll, VoidRule, DefenseStick,
			CatRocket, BalanceOrb, ExRedRibbon,
			OfficialBook, FireWheel, LemiMagesty,
			RoyalHand, CenturyLegend
		};
		using wspair = std::pair<std::wstring, std::wstring>;
		static std::map<CardType, wspair> gs_mapCardItemString;

		bool CardInit()
		{
			gs_mapCardItemString[BasicTicket] = std::make_pair(L"�ʶR��", L"��l�P��");
			gs_mapCardItemString[BasicMagic] = std::make_pair(L"�]�N�j��", L"��l�P��");
			gs_mapCardItemString[SakuraCookie] = std::make_pair(L"����", L"����");
			gs_mapCardItemString[MoonTimer] = std::make_pair(L"��ɭp", L"�_��P");
			gs_mapCardItemString[SevenColorBook] = std::make_pair(L"�C���]�k��", L"�_��P");
			gs_mapCardItemString[FantasySword] = std::make_pair(L"�n�Q�C", L"�_��P");
			gs_mapCardItemString[WatchSword] = std::make_pair(L"���[�C", L"�_��P");
			gs_mapCardItemString[MagicGlass] = std::make_pair(L"�]�k�ʦL����", L"�_��P");
			gs_mapCardItemString[MercurySword] = std::make_pair(L"���ȼCAzoth", L"�_��P");
			gs_mapCardItemString[NightmareBell] = std::make_pair(L"���L���a��", L"�_��P");
			gs_mapCardItemString[OriginMagicBullet] = std::make_pair(L"�_���]�u", L"�_��P");
			gs_mapCardItemString[SimulateNerve] = std::make_pair(L"�������gEtherite", L"�_��P");
			gs_mapCardItemString[Gourd] = std::make_pair(L"��j�]", L"�_��P");
			gs_mapCardItemString[MiniEightTrigrams] = std::make_pair(L"�g�A�K���l", L"�_��P");
			gs_mapCardItemString[EmptyMoneyBox] = std::make_pair(L"�ŪŦp�]���ɿ��c", L"�_��P");
			gs_mapCardItemString[HolyBoneCloth] = std::make_pair(L"�t�e��", L"�_��P");
			gs_mapCardItemString[IdealTownship] = std::make_pair(L"�������z�Q�m", L"�_��P");
			gs_mapCardItemString[BlackKey] = std::make_pair(L"����", L"�_��P");
			gs_mapCardItemString[MechanicalEmerald] = std::make_pair(L"����B�A", L"�_��P");
			gs_mapCardItemString[SkyDream] = std::make_pair(L"�Ѥ��M���۷Q", L"�_��P");
			gs_mapCardItemString[NightWord] = std::make_pair(L"�E�r�ݩw", L"�_��P");
			gs_mapCardItemString[AirMagicRoll] = std::make_pair(L"�t�_���Ů��]�k���b", L"�_��P");
			gs_mapCardItemString[VoidRule] = std::make_pair(L"�D�Q�ѫh", L"�_��P");
			gs_mapCardItemString[DefenseStick] = std::make_pair(L"��m��", L"�_��P");
			gs_mapCardItemString[CatRocket] = std::make_pair(L"���|�߫����b", L"�_��P");
			gs_mapCardItemString[BalanceOrb] = std::make_pair(L"������", L"�_��P");
			gs_mapCardItemString[ExRedRibbon] = std::make_pair(L"EX�����ܨ��v�a", L"�_��P");
			gs_mapCardItemString[OfficialBook] = std::make_pair(L"�����~��Gamaaliel", L"�_��P");
			gs_mapCardItemString[FireWheel] = std::make_pair(L"���V������", L"�_��P");
			gs_mapCardItemString[LemiMagesty] = std::make_pair(L"���}�����Y", L"�_��P");
			gs_mapCardItemString[RoyalHand] = std::make_pair(L"�s��O", L"�_��P");
			gs_mapCardItemString[CenturyLegend] = std::make_pair(L"�@���������ǻ�", L"�_��P");
			return true;
		}

		static bool CardInited = CardInit();
	}
}
