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
		std::wcout << L" �G��=" << pCard->GetSpellsDefence();
		std::wcout << L" �騾=" << pCard->GetPhysicsDefence();
		std::wcout << L" MP=" << pCard->GetMagic();
		std::wcout << L" �F��=" << pCard->GetSoul() << std::endl;
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

		//�_��P�w
		CardItem::SummonStack sumonstack(&System);

		//�����
		CardItem::SakuraCookieZone sakurazone(&System);

		//�l��P��
		CardItem::SummonCardZone summonCardZone(&System);

		//���ذ�
		CardItem::VoidCardZone voidCardZone(&System);

		CharacterItem::BasicCharacterItem RyougiShiki(CharacterItem::RyougiShiki, CharacterItem::Human, &System);

		//�_�l�o6�i�P��l��P��
		sumonstack.Deal(&summonCardZone, 6);

		std::wcout << L"��J�ɿ�J�t�ȴN�O�n��������.....:" << std::endl;
		int iChoose(0);
		do
		{
			//��l���⪬�A...
			RyougiShiki.ResetState();

			//�X�P���q.....
			std::wcout << L"\n�}�l�X�P���q.....:" << std::endl;
			do
			{
				const auto& HandCards = RyougiShiki.HandCardZone.GetAllCards();
				if (HandCards.empty())
					break;

				std::wcout << L"\n========================================\n���a��P��:" << std::endl;
				ShowDeqCard(RyougiShiki.HandCardZone.GetAllCards());

				std::wcout << L"\n���a�}�a��:" << std::endl;
				ShowDeqCard(RyougiShiki.CampCardZone.GetAllCards());

				std::wcout << L"\n***[ ���a���� �F��:" << RyougiShiki.GetSouls() << L" �]�O" << RyougiShiki.GetMagics() << L" ]***" << std::endl;
				std::wcout << L"\n��ܭn���X����P:";
				std::cin >> iChoose;

				if (HandCards.size() <= iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
					RyougiShiki.PostHandCard(HandCards[iChoose]);

			} while (iChoose >= 0);

			//�ʶR���q.....
			std::wcout << L"\n�}�l�ʶR���q....." << std::endl;
			RyougiShiki.CalCampOwnSouls();//Update�}�a�Ϫ��F��
			do
			{
				std::wcout << L"\n========================================\n�l��P��:" << std::endl;
				const auto& summonCards = summonCardZone.GetAllCards();
				ShowDeqCard(summonCards);

				const auto& sakuras = sakurazone.GetAllCards();
				std::wcout << L"\n����� x" << sakuras.size() << L":" << std::endl;
				if (sakuras.size())
					ShowCard(sakuras[0]);

				std::wcout << L"\n***[ ���a���� �F��:" << RyougiShiki.GetSouls() << L" �]�O" << RyougiShiki.GetMagics() << L" ]***"<<std::endl;

				std::wcout << L"\n��ܭn�ʶR����P(6������):";
				std::cin >> iChoose;

				if (iChoose == 6 && sakuras.size())
				{
					if (RyougiShiki.Buyit(sakuras[0]))
						std::wcout << L"�ʶR���榨�\" << std::endl;
					else
						std::wcout << L"�ʶR���楢��" << std::endl;
				}

				if (summonCards.size() <= iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
				{
					if (RyougiShiki.Buyit(summonCards[iChoose]))
					{
						std::wcout << L"�ʶR�_��P���\" << std::endl;
						sumonstack.Deal(&summonCardZone);
					}
					else
						std::wcout << L"�ʶR�_��P����" << std::endl;
				}

				std::wcout << L"\n��P��:" << std::endl;
				ShowDeqCard(RyougiShiki.DiscarCardZone.GetAllCards());
			} while (iChoose >= 0);

			//�}�a�Ϥ�P�������ʨ��P��
			std::wcout << L"\n========================================\n�^�X���� �}�a�Ϥ�P�������ʨ��P��...." << std::endl;
			RyougiShiki.CampCardZone.CardAllMove(&RyougiShiki.DiscarCardZone);

			
#ifdef _DEBUG
			//��v���q.....
			std::wcout << L"\nDEBUG MODE ��ʱN��P�ϲ��ܶ���....." << std::endl;
			do
			{
				const auto& DiscarCardZoneCards = RyougiShiki.DiscarCardZone.GetAllCards();
				std::wcout << L"\n��P��:" << std::endl;
				ShowDeqCard(DiscarCardZoneCards);

				std::wcout << L"\n��ܭn��v����P:";
				std::cin >> iChoose;

				if (DiscarCardZoneCards.size() <= iChoose)
					std::wcout << L"��J���X�k" << std::endl;
				else
				{
					auto target = RyougiShiki.DiscarCardZone.Choose(DiscarCardZoneCards[iChoose]);
					if (RyougiShiki.DiscarCardZone.CardMove(target, &voidCardZone))
					{
						std::wcout << L"��v���\\n���ذ�" << std::endl;
						ShowDeqCard(voidCardZone.GetAllCards());
					}
					else
						std::wcout << L"��v����" << std::endl;
				}
			} while (iChoose >= 0);
#endif // _DEBUG

			//�p���P��6�i�ٮt�X�i
			std::wcout << L"\n�}�l�N��P�ɦ^6�i...." << std::endl;
			size_t uiNeedGetCards = 6 - RyougiShiki.HandCardZone.GetAllCardNums();
			auto deals = RyougiShiki.HandStack.Deal(&RyougiShiki.HandCardZone, uiNeedGetCards);

			//�p�G�o�P�ƵP�w�����N�N��P�ϰe�^�P�w���~
			if (deals < uiNeedGetCards)
			{
				std::wcout << L"�P�w���� ��P�ϥ[�^�P�w���s�~�P..." << std::endl;
				RyougiShiki.DiscarCardZone.CardAllMove(&RyougiShiki.HandStack);
				RyougiShiki.HandStack.Shuffle();
				std::wcout << L"�P�w�ثe�P��="<< RyougiShiki.HandStack.GetCardNums()<<L" �ثe�ݭn�ɨ��P��=" << uiNeedGetCards - deals<<std::endl;
				RyougiShiki.HandStack.Deal(&RyougiShiki.HandCardZone, uiNeedGetCards - deals);
			}

			std::wcout << L"\n��J�D�t�ȫh�~��.... : ";
			std::cin >> iChoose;
		} while (iChoose >= 0);
		
	}
}