#pragma once
#include "../../Core/Card/CardStack.h"
#include "../../Core/Card/SummonStack.h"
#include "../../Core/Card/CardZone.h"
#include "../../Core/Card/SpecialCard.h"
#include "../../Core/Character/Character.h"
#include <iostream>
#include <locale>
namespace CardTest
{
	using namespace AnimeFight;

	void ShowCard(CardItem::BasicCard *pCard)
	{
		std::wcout << pCard->GetItemName() << " " << pCard->GetItemDescription();
		std::wcout << L" Cost=" << pCard->GetCost();
		std::wcout << L" 咒防=" << pCard->GetSpellsDefence();
		std::wcout << L" 體防=" << pCard->GetPhysicsDefence();
		std::wcout << L" MP=" << pCard->GetMagic();
		std::wcout << L" 靈符=" << pCard->GetSoul() << std::endl;
	}

	void ShowDeqCard(const std::deque<CardItem::BasicCard *> &deqCard)
	{
		size_t index(0);
		for (auto &iter : deqCard)
		{
			std::wcout << index<<L".";
			ShowCard(iter);
			++index;
		}
	}

	void CardTest()
	{
		std::locale::global(std::locale(""));
		std::wcout.imbue(std::locale());
		Item System(AnimeFight::System);

		//寶具牌庫
		CardItem::SummonStack sumonstack(&System);

		//櫻花餅區
		CardItem::SakuraCookieZone sakurazone(&System);

		//召喚牌區
		CardItem::SummonCardZone summonCardZone(&System);

		//間隙區
		CardItem::VoidCardZone voidCardZone(&System);

		CharacterItem::BasicCharacterItem RyougiShiki(CharacterItem::RyougiShiki, CharacterItem::Human, &System);

		//起始發6張牌到召喚牌區
		sumonstack.Deal(&summonCardZone, 6);

		std::wcout << L"輸入時輸入負值就是要直接跳離.....:" << std::endl;
		int iChoose(0);
		do
		{
			//初始角色狀態...
			RyougiShiki.ResetState();

			//出牌階段.....
			std::wcout << L"\n開始出牌階段.....:" << std::endl;
			do
			{
				const auto& HandCards = RyougiShiki.HandCardZone.GetAllCards();
				if (HandCards.empty())
					break;

				std::wcout << L"\n========================================\n玩家手牌區:" << std::endl;
				ShowDeqCard(RyougiShiki.HandCardZone.GetAllCards());

				std::wcout << L"\n玩家陣地區:" << std::endl;
				ShowDeqCard(RyougiShiki.CampCardZone.GetAllCards());

				std::wcout << L"\n***[ 玩家素質 靈符:" << RyougiShiki.GetSouls() << L" 魔力" << RyougiShiki.GetMagics() << L" ]***" << std::endl;
				std::wcout << L"\n選擇要打出的手牌:";
				std::cin >> iChoose;

				if (HandCards.size() <= iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
					RyougiShiki.PostHandCard(HandCards[iChoose]);

			} while (iChoose >= 0);

			//購買階段.....
			std::wcout << L"\n開始購買階段....." << std::endl;
			RyougiShiki.CalCampOwnSouls();//Update陣地區的靈符
			do
			{
				std::wcout << L"\n========================================\n召喚牌區:" << std::endl;
				const auto& summonCards = summonCardZone.GetAllCards();
				ShowDeqCard(summonCards);

				const auto& sakuras = sakurazone.GetAllCards();
				std::wcout << L"\n櫻花餅區 x" << sakuras.size() << L":" << std::endl;
				if (sakuras.size())
					ShowCard(sakuras[0]);

				std::wcout << L"\n***[ 玩家素質 靈符:" << RyougiShiki.GetSouls() << L" 魔力" << RyougiShiki.GetMagics() << L" ]***"<<std::endl;

				std::wcout << L"\n選擇要購買的手牌(6為櫻花餅):";
				std::cin >> iChoose;

				if (iChoose == 6 && sakuras.size())
				{
					if (RyougiShiki.Buyit(sakuras[0]))
						std::wcout << L"購買櫻花餅成功" << std::endl;
					else
						std::wcout << L"購買櫻花餅失敗" << std::endl;
				}

				if (summonCards.size() <= iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
				{
					if (RyougiShiki.Buyit(summonCards[iChoose]))
					{
						std::wcout << L"購買寶具牌成功" << std::endl;
						sumonstack.Deal(&summonCardZone);
					}
					else
						std::wcout << L"購買寶具牌失敗" << std::endl;
				}

				std::wcout << L"\n棄牌區:" << std::endl;
				ShowDeqCard(RyougiShiki.DiscarCardZone.GetAllCards());
			} while (iChoose >= 0);

			//陣地區手牌全部移動到棄牌區
			std::wcout << L"\n========================================\n回合結束 陣地區手牌全部移動到棄牌區...." << std::endl;
			RyougiShiki.CampCardZone.CardAllMove(&RyougiShiki.DiscarCardZone);

			
#ifdef _DEBUG
			//放逐階段.....
			std::wcout << L"\nDEBUG MODE 手動將棄牌區移至間隙....." << std::endl;
			do
			{
				const auto& DiscarCardZoneCards = RyougiShiki.DiscarCardZone.GetAllCards();
				std::wcout << L"\n棄牌區:" << std::endl;
				ShowDeqCard(DiscarCardZoneCards);

				std::wcout << L"\n選擇要放逐的棄牌:";
				std::cin >> iChoose;

				if (DiscarCardZoneCards.size() <= iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
				{
					auto target = RyougiShiki.DiscarCardZone.Choose(DiscarCardZoneCards[iChoose]);
					if (RyougiShiki.DiscarCardZone.CardMove(target, &voidCardZone))
					{
						std::wcout << L"放逐成功\n間隙區" << std::endl;
						ShowDeqCard(voidCardZone.GetAllCards());
					}
					else
						std::wcout << L"放逐失敗" << std::endl;
				}
			} while (iChoose >= 0);
#endif // _DEBUG

			//計算手牌離6張還差幾張
			std::wcout << L"\n開始將手牌補回6張...." << std::endl;
			size_t uiNeedGetCards = 6 - RyougiShiki.HandCardZone.GetAllCardNums();
			auto deals = RyougiShiki.HandStack.Deal(&RyougiShiki.HandCardZone, uiNeedGetCards);

			//如果發牌數牌庫不足就將棄牌區送回牌庫重洗
			if (deals < uiNeedGetCards)
			{
				std::wcout << L"牌庫不足 棄牌區加回牌庫重新洗牌..." << std::endl;
				RyougiShiki.DiscarCardZone.CardAllMove(&RyougiShiki.HandStack);
				RyougiShiki.HandStack.Shuffle();
				std::wcout << L"牌庫目前牌數="<< RyougiShiki.HandStack.GetCardNums()<<L" 目前需要補足牌數=" << uiNeedGetCards - deals<<std::endl;
				RyougiShiki.HandStack.Deal(&RyougiShiki.HandCardZone, uiNeedGetCards - deals);
			}

			std::wcout << L"\n輸入非負值則繼續.... : ";
			std::cin >> iChoose;
		} while (iChoose >= 0);
		
	}
}