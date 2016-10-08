#pragma once

#include <chrono>

namespace AnimeFight
{
	class TimeNode final
	{
	public:
		using TimeType = std::chrono::system_clock;
		enum NodeState
		{
			None,
			Staying,
			Hanging,
			Passed
		};

	public:
		explicit TimeNode(long long In_lNumber);
		~TimeNode();

		// ���o�s��
		const long long &GetNumber();

		// ���oNode�ثe�����A
		const NodeState& GetSate();

		//	�i�J�o��Node
		bool Enter();

		//	����A(Enable��Ture�����A�ܬ�Hang��, �N���|�~��p�ⰱ�d�ɶ�)
		bool Hang(bool bEnable);

		//	���}�o��Node
		bool Leave();

		//	���o���d�b�o��Node���ɶ�
		long long GetStayDurationMs();

		/*	���o�i�J�ɶ��I(Real System Clock)
			�Y�^��False�N���A��None
		 */
		bool GetEnterTimePoint(TimeType::time_point &Out_Point);

		/*	���o���}�ɶ��I(Real System Clock)
			�Y�^��False�N���A�S���ܧ�Passed
		*/
		bool GetLeaveTimePoint(TimeType::time_point &Out_Point);

	private:
		// ��sStayMs
		inline void UpdateStayMs();

		//�ۤv�o�Ӹ`�I���s��
		long long m_lNumber;

		//�O���ۤv�����A
		NodeState m_NodeState;

		//�i�J���ɶ��I, ���}���ɶ��I, �Ȱ����ɶ��I
		TimeType::time_point m_EnterTp, m_LeaveTp, mHangTp;

		//�O���ݦb�o��Node���ɶ�
		std::chrono::milliseconds	m_stayms;
	};
}