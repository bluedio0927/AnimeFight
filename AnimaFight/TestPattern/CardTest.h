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
		std::wcout << L" �G��=" << pCard->GetSpellsDefence();
		std::wcout << L" �騾=" << pCard->GetPhysicsDefence();
		std::wcout << L" MP=" << pCard->GetMagic();
		std::wcout << L" �F��=" << pCard->GetSoul() << std::endl;
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
		std::wcout << L"\n***[ ���a���� �F��:" << pCharacter->GetSouls() << L" �]�O" << pCharacter->GetMagics() << L" �ޯ��I" << pCharacter->GetSkillPoint() << L" ]***" << std::endl;
	}

	void CardTest()
	{
		std::locale::global(std::locale(""));
		std::wcout.imbue(std::locale());

		std::unique_ptr<Core::GameCore> pSystem(new Core::GameCore(new CardItem::SummonStack, new CardItem::SummonCardZone, new CardItem::SakuraCookieZone, new CardItem::VoidCardZone));
		
		CharacterItem::BasicCharacterItem* pRyougiShiki = CharacterItem::CreateCharacter(CharacterItem::RyougiShiki, CharacterItem::Human, pSystem.get());

		//�_�l�o6�i�P��l��P��
		pSystem->Summon(6);
		
		std::wcout << L"��J�ɿ�J�t�ȴN�O�n��������.....:" << std::endl;
		int iChoose(0);
		do
		{
			//��l���⪬�A...
			pRyougiShiki->ResetState();
		
			//�X�P���q.....
			std::wcout << L"\n�}�l�X�P���q.....:" << std::endl;
			do
			{
				const auto& HandCards = pRyougiShiki->HandCardZone->GetAllCards();
				if (HandCards.empty())
					break;
		
				std::wcout << L"\n========================================\n���a��P��:" << std::endl;
				ShowDeqCard(pRyougiShiki->HandCardZone->GetAllCards());
		
				std::wcout << L"\n��ܭn���X����P:";
				std::cin >> iChoose;
		
				if (HandCards.size() <= (unsigned int)iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
					pRyougiShiki->PostHandCard(HandCards[iChoose]);
		
				std::wcout << L"\n���a�}�a��:" << std::endl;
				ShowDeqCard(pRyougiShiki->CampCardZone->GetAllCards());

				ShowCharacter(pRyougiShiki);

			} while (iChoose >= 0);
		
			//�ʶR���q.....
			std::wcout << L"\n�}�l�ʶR���q....." << std::endl;
			pRyougiShiki->CalCampOwnSouls();//Update�}�a�Ϫ��F��
			do
			{
				std::wcout << L"\n========================================\n�l��P��:" << std::endl;
				const auto& summonCards = pSystem->SummonZone().GetAllCards();
				ShowDeqCard(summonCards);
		
				const auto& sakuras = pSystem->SakuraZone().GetAllCards();
				std::wcout << L"\n����� x" << sakuras.size() << L":" << std::endl;
				if (sakuras.size())
				{
					std::wcout << "6.";
					ShowCard(sakuras[0]);
				}

				ShowCharacter(pRyougiShiki);
		
				std::wcout << L"\n��ܭn�ʶR����P:";
				std::cin >> iChoose;
		
				if (iChoose == 6 && sakuras.size())
				{
					if (pRyougiShiki->Buyit(sakuras[0]))
						std::wcout << L"�ʶR���榨�\" << std::endl;
					else
						std::wcout << L"�ʶR���楢��" << std::endl;
				}
		
				if (summonCards.size() <= (unsigned int)iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
				{
					if (pRyougiShiki->Buyit(summonCards[iChoose]))
					{
						std::wcout << L"�ʶR�_��P���\" << std::endl;
						pSystem->Summon();
					}
					else
						std::wcout << L"�ʶR�_��P����" << std::endl;
				}
		
				std::wcout << L"\n��P��:" << std::endl;
				ShowDeqCard(pRyougiShiki->DiscarCardZone->GetAllCards());
			} while (iChoose >= 0);
		
			//�}�a�Ϥ�P�������ʨ��P��
			std::wcout << L"\n========================================\n�^�X���� �}�a�Ϥ�P�������ʨ��P��...." << std::endl;
			pRyougiShiki->CampCardZone->CardAllMove(pRyougiShiki->DiscarCardZone);
		
			
//#ifdef _DEBUG
			//��v���q.....
			std::wcout << L"\nDEBUG MODE ��ʱN��P�ϲ��ܶ���....." << std::endl;
			do
			{
				const auto& DiscarCardZoneCards = pRyougiShiki->DiscarCardZone->GetAllCards();
				std::wcout << L"\n��P��:" << std::endl;
				ShowDeqCard(DiscarCardZoneCards);
		
				std::wcout << L"\n��ܭn��v����P:";
				std::cin >> iChoose;
		
				if (DiscarCardZoneCards.size() <= (unsigned int)iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
				{
					if (pRyougiShiki->ExileDiscardCard(DiscarCardZoneCards[iChoose]))
					{
						std::wcout << L"��v���\\n���ذ�" << std::endl;
						ShowDeqCard(pSystem->VoidZone().GetAllCards());
					}
					else
						std::wcout << L"��v����" << std::endl;
				}
			} while (iChoose >= 0);
//#endif // _DEBUG
		
			//�p���P��6�i�ٮt�X�i
			std::wcout << L"\n�}�l�N��P�ɦ^6�i...." << std::endl;
			size_t uiNeedGetCards = 6 - pRyougiShiki->HandCardZone->GetAllCardNums();
			auto deals = pRyougiShiki->GetHandCard(uiNeedGetCards);
		
			//�p�G�o�P�ƵP�w�����N�N��P�ϰe�^�P�w���~
			if (deals < uiNeedGetCards)
			{
				std::wcout << L"�P�w���� ��P�ϥ[�^�P�w���s�~�P..." << std::endl;
				pRyougiShiki->DiscarCardZone->CardAllMove(pRyougiShiki->HandStack);
				pRyougiShiki->HandStack->Shuffle();
				std::wcout << L"�P�w�ثe�P��="<< pRyougiShiki->HandStack->GetCardNums()<<L" �ثe�ݭn�ɨ��P��=" << uiNeedGetCards - deals<<std::endl;
				pRyougiShiki->GetHandCard(uiNeedGetCards - deals);
			}
		
			std::wcout << L"\n��J�D�t�ȫh�~��.... : ";
			std::cin >> iChoose;
		} while (iChoose >= 0);
		
	}
}