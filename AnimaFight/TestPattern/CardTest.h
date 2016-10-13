#pragma once
#include "../../Core/Card/CardStack.h"
#include "../../Core/Card/CardZone.h"
#include "../../Core/Card/SpecialCard.h"
#include "../../Core/Card/SpecialCardStack.h"
#include "../../Core/Character/CharacterFactory.h"
#include "../../Core/System/GameCore.h"
#include <iostream>
#include <locale>
#include <memory>
namespace CardTest
{
	using namespace AnimeFight;

	void ShowCard(CardItem::BasicCard *pCard)
	{
		std::wcout << pCard->GetItemName();
		std::wcout << L" Cost=" << pCard->GetCost();
		std::wcout << L" 咒防=" << pCard->GetSpellsDefence();
		std::wcout << L" 體防=" << pCard->GetPhysicsDefence();
		std::wcout << L" MP=" << pCard->GetMagic();
		std::wcout << L" 靈符=" << pCard->GetSoul() << std::endl;
		std::wcout << pCard->GetItemDescription() << std::endl << std::endl;
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

	void ShowCharacter(CharacterItem::BasicCharacterItem* pCharacter)
	{
		std::wcout << L"\n***[ 玩家素質 靈符:" << pCharacter->GetSouls() << L" 魔力" << pCharacter->GetMagics() << L" 技能點" << pCharacter->GetSkillPoint() << L" ]***" << std::endl;
	}

	void CardTest()
	{
		std::locale::global(std::locale(""));
		std::wcout.imbue(std::locale());

		std::unique_ptr<Core::GameCore> pSystem(new Core::GameCore(new CardItem::SummonStack, new CardItem::SummonCardZone, new CardItem::SakuraCookieZone, new CardItem::VoidCardZone));
		
		CharacterItem::BasicCharacterItem* pRyougiShiki = CharacterItem::CreateCharacter(CharacterItem::RyougiShiki, CharacterItem::Human, pSystem.get());

		//起始發6張牌到召喚牌區
		pSystem->Summon(6);
		
		std::wcout << L"輸入時輸入負值就是要直接跳離.....:" << std::endl;
		int iChoose(0);
		do
		{
			//初始角色狀態...
			pRyougiShiki->ResetState();
		
			//出牌階段.....
			std::wcout << L"\n開始出牌階段.....:" << std::endl;
			do
			{
				const auto& HandCards = pRyougiShiki->HandCardZone->GetAllCards();
				if (HandCards.empty())
					break;
		
				std::wcout << L"\n========================================\n玩家手牌區:" << std::endl;
				ShowDeqCard(pRyougiShiki->HandCardZone->GetAllCards());
		
				std::wcout << L"\n選擇要打出的手牌:";
				std::cin >> iChoose;
		
				if (HandCards.size() <= (unsigned int)iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
					pRyougiShiki->PostHandCard(HandCards[iChoose]);
		
				std::wcout << L"\n玩家陣地區:" << std::endl;
				ShowDeqCard(pRyougiShiki->CampCardZone->GetAllCards());

				ShowCharacter(pRyougiShiki);

			} while (iChoose >= 0);
		
			//購買階段.....
			std::wcout << L"\n開始購買階段....." << std::endl;
			pRyougiShiki->CalCampOwnSouls();//Update陣地區的靈符
			do
			{
				std::wcout << L"\n========================================\n召喚牌區:" << std::endl;
				const auto& summonCards = pSystem->SummonZone().GetAllCards();
				ShowDeqCard(summonCards);
		
				const auto& sakuras = pSystem->SakuraZone().GetAllCards();
				std::wcout << L"\n櫻花餅區 x" << sakuras.size() << L":" << std::endl;
				if (sakuras.size())
				{
					std::wcout << "6.";
					ShowCard(sakuras[0]);
				}

				ShowCharacter(pRyougiShiki);
		
				std::wcout << L"\n選擇要購買的手牌:";
				std::cin >> iChoose;
		
				if (iChoose == 6 && sakuras.size())
				{
					if (pRyougiShiki->Buyit(sakuras[0]))
						std::wcout << L"購買櫻花餅成功" << std::endl;
					else
						std::wcout << L"購買櫻花餅失敗" << std::endl;
				}
		
				if (summonCards.size() <= (unsigned int)iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
				{
					if (pRyougiShiki->Buyit(summonCards[iChoose]))
					{
						std::wcout << L"購買寶具牌成功" << std::endl;
						pSystem->Summon();
					}
					else
						std::wcout << L"購買寶具牌失敗" << std::endl;
				}
		
				std::wcout << L"\n棄牌區:" << std::endl;
				ShowDeqCard(pRyougiShiki->DiscarCardZone->GetAllCards());
			} while (iChoose >= 0);
		
			//陣地區手牌全部移動到棄牌區
			std::wcout << L"\n========================================\n回合結束 陣地區手牌全部移動到棄牌區...." << std::endl;
			pRyougiShiki->CampCardZone->CardAllMove(pRyougiShiki->DiscarCardZone);
		
			
//#ifdef _DEBUG
			//放逐階段.....
			std::wcout << L"\nDEBUG MODE 手動將棄牌區移至間隙....." << std::endl;
			do
			{
				const auto& DiscarCardZoneCards = pRyougiShiki->DiscarCardZone->GetAllCards();
				std::wcout << L"\n棄牌區:" << std::endl;
				ShowDeqCard(DiscarCardZoneCards);
		
				std::wcout << L"\n選擇要放逐的棄牌:";
				std::cin >> iChoose;
		
				if (DiscarCardZoneCards.size() <= (unsigned int)iChoose)
					std::wcout << L"輸入不合法" << std::endl;
				else
				{
					if (pRyougiShiki->ExileDiscardCard(DiscarCardZoneCards[iChoose]))
					{
						std::wcout << L"放逐成功\n間隙區" << std::endl;
						ShowDeqCard(pSystem->VoidZone().GetAllCards());
					}
					else
						std::wcout << L"放逐失敗" << std::endl;
				}
			} while (iChoose >= 0);
//#endif // _DEBUG
		
			//計算手牌離6張還差幾張
			std::wcout << L"\n開始將手牌補回6張...." << std::endl;
			size_t uiNeedGetCards = 6 - pRyougiShiki->HandCardZone->GetAllCardNums();
			auto deals = pRyougiShiki->GetHandCard(uiNeedGetCards);
		
			//如果發牌數牌庫不足就將棄牌區送回牌庫重洗
			if (deals < uiNeedGetCards)
			{
				std::wcout << L"牌庫不足 棄牌區加回牌庫重新洗牌..." << std::endl;
				pRyougiShiki->DiscarCardZone->CardAllMove(pRyougiShiki->HandStack);
				pRyougiShiki->HandStack->Shuffle();
				std::wcout << L"牌庫目前牌數="<< pRyougiShiki->HandStack->GetCardNums()<<L" 目前需要補足牌數=" << uiNeedGetCards - deals<<std::endl;
				pRyougiShiki->GetHandCard(uiNeedGetCards - deals);
			}
		
			std::wcout << L"\n輸入非負值則繼續.... : ";
			std::cin >> iChoose;
		} while (iChoose >= 0);
		
	}
}