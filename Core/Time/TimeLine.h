#pragma once

#include "TimeNode.h"

#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <queue>
#include <condition_variable>

namespace AnimeFight
{
	class TimeLine
	{
	public:
		enum CMDTYPE
		{
			Hang, //����p��`�I�����d�ɶ�
			Keep, //���s�p��`�I�����d�ɶ�
			GoNext  //�������U�@�Ӹ`�I����(�ݭn�O�DHang�����A)
		};

		// �ǤJ�ɶ��b���X�Ӯɶ��`�I
		TimeLine(size_t In_TimepointNums);
		virtual ~TimeLine();

		// ���o���X�Ӯɶ��`�I
		size_t GetTimeNodeNums();

		// ���o�ثe�b�b���Ӯɶ��`�I
		size_t GetNowStayPointIndex();

		/*	�]�w�ɶ��I�����d�ɶ��W��, Index�q0�}�l, In_Timeoutms�]��0�ɥN��ݭn����Next CMD�~�|���},	�Y���]�w�h�N��ߧY�g�L�o�Ӹ`�I.
			�Y�^�ǥ��ѥN��Index�W�L�`�I��
		*/
		bool SetTimeNodeStayTimeout(size_t In_NodeIndex, long long In_Timeoutms);

		//  �����ɶ��I�����d�ɶ��W��, Index�q0�}�l
		void UnSetTimeNodeStayTimeout(size_t In_NodeIndex);

		//  ��JCMD, TimeLine�ۤv������Thread�|PopCMD(�D�n�O���t�@��Thread�I�s, �ѨM�|Block���禡)
		void PushCMD(CMDTYPE In_CMD);

		// �i�J�ɶ��b(�|Block��, ����ɶ��`�I�����d�ɶ��W�����󺡨������})
		void Enter();

		// ���ʨ�U�@�Ӯɶ��`�I(�|Block��, ����ɶ��`�I�����d�ɶ��W�����󺡨������})
		void Next();

		// "���e����"��Y�@�Ӯɶ��`�I(�|Block��, ����ɶ��`�I�����d�ɶ��W�����󺡨������})
		// �Y���Ჾ�ʷ|�^�ǥ���, Index�q0�}�l
		bool ForwardTo(size_t In_PointIndex);

		// �P�_�O�_�w�g���槹�̫�@�Ӹ`�I
		bool IsEnd();

		// �����ɶ��b���B��P�Ҧ���Block�ާ@
		void Cancel();

	private:
		// ��Pop CMD Thread ���檺Function..
		void DoPopCMD();

		void DoLeave();

		void GotoNode(std::unique_lock<std::mutex> &unilck, size_t Index);

		bool GetTimeNodeStayTimeout(size_t In_NodeIndex, long long &Out_Timeoutms);
		// �P�_�O�_�w�i�J�P���}�ɶ��b��Flag
		bool m_bEnter, m_bLeave;

		// �ثe���d���ɶ��`�IIndex
		size_t m_stayTimePointIndex;

		// �֦����Ҧ��`�I
		std::vector<TimeNode>	m_vecTimeNodes;

		// �ХܩҦ��`�I���O�_�w�g�������}Block����Flag
		std::vector<bool>		m_vecTimeNodesLeaveFlag;

		// �x�s�ɶ��I�����d�ɶ��W����MAP
		std::map<size_t, long long> m_mapTimeNodeLeaveMode;

		// CMDQueue
		std::queue<CMDTYPE> m_queNODECMD;

		//Thread Control...
		//Pop CMD Queue Thread
		std::thread	*m_thread;

		//Thread Safe
		std::mutex	m_mutex;

		std::condition_variable m_cvNext, m_cvPop;
	};
}