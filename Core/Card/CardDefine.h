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
			gs_mapCardItemString[BasicTicket] = std::make_pair(L"購買卷", L"初始牌組");
			gs_mapCardItemString[BasicMagic] = std::make_pair(L"魔術迴路", L"初始牌組");
			gs_mapCardItemString[SakuraCookie] = std::make_pair(L"櫻花餅", L"櫻花餅");
			gs_mapCardItemString[MoonTimer] = std::make_pair(L"月時計", L"寶具牌");
			gs_mapCardItemString[SevenColorBook] = std::make_pair(L"七色魔法書", L"寶具牌");
			gs_mapCardItemString[FantasySword] = std::make_pair(L"緋想劍", L"寶具牌");
			gs_mapCardItemString[WatchSword] = std::make_pair(L"樓觀劍", L"寶具牌");
			gs_mapCardItemString[MagicGlass] = std::make_pair(L"魔法封印眼鏡", L"寶具牌");
			gs_mapCardItemString[MercurySword] = std::make_pair(L"水銀劍Azoth", L"寶具牌");
			gs_mapCardItemString[NightmareBell] = std::make_pair(L"夢魘的鈴噹", L"寶具牌");
			gs_mapCardItemString[OriginMagicBullet] = std::make_pair(L"起源魔彈", L"寶具牌");
			gs_mapCardItemString[SimulateNerve] = std::make_pair(L"模擬神經Etherite", L"寶具牌");
			gs_mapCardItemString[Gourd] = std::make_pair(L"伊吹瓢", L"寶具牌");
			gs_mapCardItemString[MiniEightTrigrams] = std::make_pair(L"迷你八卦爐", L"寶具牌");
			gs_mapCardItemString[EmptyMoneyBox] = std::make_pair(L"空空如也的賽錢箱", L"寶具牌");
			gs_mapCardItemString[HolyBoneCloth] = std::make_pair(L"聖骸布", L"寶具牌");
			gs_mapCardItemString[IdealTownship] = std::make_pair(L"遙遠的理想鄉", L"寶具牌");
			gs_mapCardItemString[BlackKey] = std::make_pair(L"黑鍵", L"寶具牌");
			gs_mapCardItemString[MechanicalEmerald] = std::make_pair(L"機械翡翠", L"寶具牌");
			gs_mapCardItemString[SkyDream] = std::make_pair(L"天之杯的幻想", L"寶具牌");
			gs_mapCardItemString[NightWord] = std::make_pair(L"九字兼定", L"寶具牌");
			gs_mapCardItemString[AirMagicRoll] = std::make_pair(L"聖奇奧空氣魔法卷軸", L"寶具牌");
			gs_mapCardItemString[VoidRule] = std::make_pair(L"非想天則", L"寶具牌");
			gs_mapCardItemString[DefenseStick] = std::make_pair(L"制禦棒", L"寶具牌");
			gs_mapCardItemString[CatRocket] = std::make_pair(L"阿魯貓型火箭", L"寶具牌");
			gs_mapCardItemString[BalanceOrb] = std::make_pair(L"陰陽玉", L"寶具牌");
			gs_mapCardItemString[ExRedRibbon] = std::make_pair(L"EX紅色變身緞帶", L"寶具牌");
			gs_mapCardItemString[OfficialBook] = std::make_pair(L"正式外典Gamaaliel", L"寶具牌");
			gs_mapCardItemString[FireWheel] = std::make_pair(L"火燄的車輪", L"寶具牌");
			gs_mapCardItemString[LemiMagesty] = std::make_pair(L"蕾咪的威嚴", L"寶具牌");
			gs_mapCardItemString[RoyalHand] = std::make_pair(L"御手板", L"寶具牌");
			gs_mapCardItemString[CenturyLegend] = std::make_pair(L"世紀末風神傳說", L"寶具牌");
			return true;
		}

		static bool CardInited = CardInit();
	}
}
