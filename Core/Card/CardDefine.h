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
			gs_mapCardItemString[BasicTicket] = std::make_pair(L"���M���ʪ���", L"��l�P��");
			gs_mapCardItemString[BasicMagic] = std::make_pair(L"�h�����]�N�j��", L"��l�P��");
			gs_mapCardItemString[SakuraCookie] = std::make_pair(L"����", L"�ޯ��+1");
			gs_mapCardItemString[MoonTimer] = std::make_pair(L"��ɭp", L"�I�q�ؼй��F�A��1�i�P");
			gs_mapCardItemString[SevenColorBook] = std::make_pair(L"�C���]�k��", L"�^�_�ؼЪ��a1�ͩR");
			gs_mapCardItemString[FantasySword] = std::make_pair(L"�n�Q���C", L"�A�i�H�q��P�α�P�襤��v1�i�P�F�����ؼй��2��N�ˮ`");
			gs_mapCardItemString[WatchSword] = std::make_pair(L"���[�C", L"�Ѱ��ؼЪ��a�i�T�D�j�Ρi�ʦL�j�ĪG�F�����ؼй��3��N�ˮ`");
			gs_mapCardItemString[MagicGlass] = std::make_pair(L"�]���ʦL����", L"�i���{�j�i�J�l��ϮɡA�Ҧ����a��1�i�P\n�ؼй���1�i�P�F�A���ޯ�� + 1");
			gs_mapCardItemString[MercurySword] = std::make_pair(L"���ȼCAzoth", L"�����ۤv1�����ˮ`�F�A�i�H�q�l��ϩ�v1�i�P");
			gs_mapCardItemString[NightmareBell] = std::make_pair(L"���L���a��", L"���1���G�N���P�����ؼж��ͤ⤤�F�ؼж��ͱ�1�i�P�A�A��o3�]�O");
			gs_mapCardItemString[OriginMagicBullet] = std::make_pair(L"�_���]�u", L"�����ؼй��1�����ˮ`");
			gs_mapCardItemString[SimulateNerve] = std::make_pair(L"�������gEtherite", L"�i�ʦL�j�ؼй��");
			gs_mapCardItemString[Gourd] = std::make_pair(L"��j�]", L"���{�j�i�J�l��ϮɡA�Ҧ����a��1�i�P\n�N�A��P��@�i�P�m��P�w���A�p�G�����l��O�Τp��5�A�h�i�H�����m�J�⤤");
			gs_mapCardItemString[MiniEightTrigrams] = std::make_pair(L"�g�A�K���l", L"�ޯ��+1�F�����ؼй��3�G�N�ˮ`");
			gs_mapCardItemString[EmptyMoneyBox] = std::make_pair(L"�ŪŦp�]���ɿ��c", L"�A��2�i�P�F�i�H�q�l��ϩ�v1�i�P");
			gs_mapCardItemString[HolyBoneCloth] = std::make_pair(L"�t�e��", L"�ŧi�@�i�P�W�A�M���1�i�P�îi�ܡA�p�G�O�A�ҫŧi���P�A�h�A�i�H�i�y�b�j�ؼй��");
			gs_mapCardItemString[IdealTownship] = std::make_pair(L"�������z�Q�m", L"�i���{�j�i�J�l��ϮɡA�Ҧ��H�^�_2�ͩR\n�ؼФͤ誱�a��o�i���ɡj�F�H���P���m�ɡA�Y�A���Q�����A�^�_4�ͩR�i���P���m�ɶi�J��P��j");
			gs_mapCardItemString[BlackKey] = std::make_pair(L"����", L"�I�q�ؼй��F�Φ��P���m��A�p�G�A�S���Q�����A�h�����ˮ`�ӷ����a1�I�����ˮ`�F�i���P���m��i�J��P��j");
			gs_mapCardItemString[MechanicalEmerald] = std::make_pair(L"����B�A", L"���P���|���}�A���}�a�ϡC�A�C���������ɡA�i�N���ءB��P�α�P�襤�@�i�P���¤U�|��b���P�U�A�̦h�ֿn2�i�C�C���@�i�|�񪺵P�A����B�A��o�ݩ��]�O+2/�F��+2");
			gs_mapCardItemString[SkyDream] = std::make_pair(L"�Ѥ��M���۷Q", L"�i���{�j���P�i�J�l��ϮɡA�C�Ӷ�����o1�F�ߡF�j��N���ܵP�~�P�ñN�i�R�B���]�j½�}�m��P�w��\n�L�k�q�l��ϳQ��v�F�����N�l��Ϥ@�i�P�m��ؼФͤ誱�a���P�w��");
			gs_mapCardItemString[NightWord] = std::make_pair(L"�E�r�ݩw", L"�i���{�j�C�쪱�a�i�H�q��P�α�P�襤��v1�i�P\n	�A���ޯ�� + 1�F�i�H�q��P�α�P�襤��v1�i�P");
			gs_mapCardItemString[AirMagicRoll] = std::make_pair(L"�t�_���Ů��]�k���b", L"�����ؼй��2�G�N�ˮ`");
			gs_mapCardItemString[VoidRule] = std::make_pair(L"�D�Q�ѫh", L"�i���{�j�Ҧ����a��e�ͩR�ȱj�歰��1\n�����ѨM½�}�����ܵP�A�ñN���P��v�i���P�Ω󨾿m�ɡA�N��m�J��P��j");
			gs_mapCardItemString[DefenseStick] = std::make_pair(L"��m��", L"�N��P���̦h2�i�P���¤U�|��b���P�U���A�A��o�B�~�i�|��i��x2�j���]�O��");
			gs_mapCardItemString[CatRocket] = std::make_pair(L"���|�߫����b", L"�A�i�H�q��P�α�P�襤��v1�i�P�F�T�D�A�ۤv");
			gs_mapCardItemString[BalanceOrb] = std::make_pair(L"������", L"�F��+1�F�^�_�ؼФH������2�ͩR�õ����ؼФH�~���1�����ˮ`");
			gs_mapCardItemString[ExRedRibbon] = std::make_pair(L"EX�����ܨ��v�a", L"���P�Q��v�ɡA��e�^�X���a�^�_3�ͩR�A��1�i�P");
			gs_mapCardItemString[OfficialBook] = std::make_pair(L"�����~��Gamaaliel", L"���P���m�ɡA�A�i�H�B�~��X�i�P�A�W�[X�I���m��");
			gs_mapCardItemString[FireWheel] = std::make_pair(L"���V������", L"�i���{�j��e�^�X���a�q��P��M�l��ϦU��v1�i�P\n�ؼЪ��a��o���N1�Ө䨤��i�H�֦����ޯ���ܪ�");
			gs_mapCardItemString[LemiMagesty] = std::make_pair(L"���}�����Y", L"���i�P�A�M���2�i�P");
			gs_mapCardItemString[RoyalHand] = std::make_pair(L"�t�w�D�h���C", L"�A�U���������ˮ`�a���i��z�j");
			gs_mapCardItemString[CenturyLegend] = std::make_pair(L"�@���������ǻ�", L"�i���{�j�����o���ɡA��L���a�U��1�i�P\n���⵹���A�ˮ`�ɡA�A�i�H�����m�é�v���d�A�M�᧹���K�̦����ˮ`�C���d�L�k���}����");
			return true;
		}

		static bool CardInited = CardInit();
	}
}
