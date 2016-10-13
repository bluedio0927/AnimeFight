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

		enum CardEffect
		{
			Come,
			Exile,
			Defence,
			Post
		};

		using wspair = std::pair<std::wstring, std::wstring>;
		static std::map<CardType, wspair> gs_mapCardItemString;

		bool CardInit()
		{
			gs_mapCardItemString[BasicTicket] = std::make_pair(L"香霖堂購物券", L"初始牌組");
			gs_mapCardItemString[BasicMagic] = std::make_pair(L"士郎的魔術迴路", L"初始牌組");
			gs_mapCardItemString[SakuraCookie] = std::make_pair(L"櫻花餅", L"技能值+1");
			gs_mapCardItemString[MoonTimer] = std::make_pair(L"月時計", L"沉默目標對手；你抓1張牌");
			gs_mapCardItemString[SevenColorBook] = std::make_pair(L"七色魔法書", L"回復目標玩家1生命");
			gs_mapCardItemString[FantasySword] = std::make_pair(L"緋想之劍", L"你可以從手牌或棄牌堆中放逐1張牌；給予目標對手2體術傷害");
			gs_mapCardItemString[WatchSword] = std::make_pair(L"樓觀劍", L"解除目標玩家【禁錮】或【封印】效果；給予目標對手3體術傷害");
			gs_mapCardItemString[MagicGlass] = std::make_pair(L"魔眼封印眼鏡", L"【降臨】進入召喚區時，所有玩家棄1張牌\n目標對手棄1張牌；你的技能值 + 1");
			gs_mapCardItemString[MercurySword] = std::make_pair(L"水銀劍Azoth", L"給予自己1直接傷害；你可以從召喚區放逐1張牌");
			gs_mapCardItemString[NightmareBell] = std::make_pair(L"夢魘的鈴噹", L"選擇1項：將此牌給予目標隊友手中；目標隊友棄1張牌，你獲得3魔力");
			gs_mapCardItemString[OriginMagicBullet] = std::make_pair(L"起源魔彈", L"給予目標對手1直接傷害");
			gs_mapCardItemString[SimulateNerve] = std::make_pair(L"模擬神經Etherite", L"【封印】目標對手");
			gs_mapCardItemString[Gourd] = std::make_pair(L"伊吹瓢", L"降臨】進入召喚區時，所有玩家抓1張牌\n將你棄牌堆一張牌置於牌庫頂，如果它的召喚費用小於5，則可以直接置入手中");
			gs_mapCardItemString[MiniEightTrigrams] = std::make_pair(L"迷你八卦爐", L"技能值+1；給予目標對手3咒術傷害");
			gs_mapCardItemString[EmptyMoneyBox] = std::make_pair(L"空空如也的賽錢箱", L"你抓2張牌；可以從召喚區放逐1張牌");
			gs_mapCardItemString[HolyBoneCloth] = std::make_pair(L"聖骸布", L"宣告一張牌名，然後抓1張牌並展示，如果是你所宣告的牌，則你可以【魅惑】目標對手");
			gs_mapCardItemString[IdealTownship] = std::make_pair(L"遙遠的理想鄉", L"【降臨】進入召喚區時，所有人回復2生命\n目標友方玩家獲得【結界】；以此牌防禦時，若你未被擊殺，回復4生命【此牌防禦時進入棄牌堆】");
			gs_mapCardItemString[BlackKey] = std::make_pair(L"黑鍵", L"沉默目標對手；用此牌防禦後，如果你沒有被擊殺，則給予傷害來源玩家1點直接傷害；【此牌防禦後進入棄牌堆】");
			gs_mapCardItemString[MechanicalEmerald] = std::make_pair(L"機械翡翠", L"此牌不會離開你的陣地區。你每次擊殺對手時，可將間隙、手牌或棄牌堆中一張牌面朝下疊放在此牌下，最多累積2張。每有一張疊放的牌，機械翡翠獲得屬性魔力+2/靈符+2");
			gs_mapCardItemString[SkyDream] = std::make_pair(L"天之杯的幻想", L"【降臨】此牌進入召喚區時，每個隊伍獲得1靈脈；強制將異變牌洗牌並將【命運長夜】翻開置於牌庫頂\n無法從召喚區被放逐；直接將召喚區一張牌置於目標友方玩家的牌庫頂");
			gs_mapCardItemString[NightWord] = std::make_pair(L"九字兼定", L"【降臨】每位玩家可以從手牌或棄牌堆中放逐1張牌\n	你的技能值 + 1；可以從手牌或棄牌堆中放逐1張牌");
			gs_mapCardItemString[AirMagicRoll] = std::make_pair(L"聖奇奧空氣魔法卷軸", L"給予目標對手2咒術傷害");
			gs_mapCardItemString[VoidRule] = std::make_pair(L"非想天則", L"【降臨】所有玩家當前生命值強行降為1\n直接解決翻開的異變牌，並將此牌放逐【此牌用於防禦時，將其置入棄牌堆】");
			gs_mapCardItemString[DefenseStick] = std::make_pair(L"制禦棒", L"將手牌中最多2張牌面朝下疊放在此牌下面，你獲得額外【疊放張數x2】的魔力值");
			gs_mapCardItemString[CatRocket] = std::make_pair(L"阿魯貓型火箭", L"你可以從手牌或棄牌堆中放逐1張牌；禁錮你自己");
			gs_mapCardItemString[BalanceOrb] = std::make_pair(L"陰陽玉", L"靈脈+1；回復目標人類角色2生命並給予目標人外對手1直接傷害");
			gs_mapCardItemString[ExRedRibbon] = std::make_pair(L"EX紅色變身緞帶", L"當此牌被放逐時，當前回合玩家回復3生命，抓1張牌");
			gs_mapCardItemString[OfficialBook] = std::make_pair(L"正式外典Gamaaliel", L"此牌防禦時，你可以額外棄X張牌，增加X點防禦值");
			gs_mapCardItemString[FireWheel] = std::make_pair(L"火燄的車輪", L"【降臨】當前回合玩家從棄牌堆和召喚區各放逐1張牌\n目標玩家獲得任意1個其角色可以擁有的技能指示物");
			gs_mapCardItemString[LemiMagesty] = std::make_pair(L"蕾咪的威嚴", L"抓兩張牌，然後棄2張牌");
			gs_mapCardItemString[RoyalHand] = std::make_pair(L"聖德道士之笏", L"你下次給予的傷害帶有【穿透】");
			gs_mapCardItemString[CenturyLegend] = std::make_pair(L"世紀末風神傳說", L"【降臨】文文獲得結界，其他玩家各抓1張牌\n當對手給予你傷害時，你可以不防禦並放逐此卡，然後完全免疫此次傷害。此卡無法離開間隙");
			return true;
		}

		static bool CardInited = CardInit();
	}
}
