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

		// 取得編號
		const long long &GetNumber();

		// 取得Node目前的狀態
		const NodeState& GetSate();

		//	進入這個Node
		bool Enter();

		//	停止狀態(Enable為Ture讓狀態變為Hang時, 就不會繼續計算停留時間)
		bool Hang(bool bEnable);

		//	離開這個Node
		bool Leave();

		//	取得停留在這個Node的時間
		long long GetStayDurationMs();

		/*	取得進入時間點(Real System Clock)
			若回傳False代表狀態為None
		 */
		bool GetEnterTimePoint(TimeType::time_point &Out_Point);

		/*	取得離開時間點(Real System Clock)
			若回傳False代表狀態沒有變更為Passed
		*/
		bool GetLeaveTimePoint(TimeType::time_point &Out_Point);

	private:
		// 更新StayMs
		inline void UpdateStayMs();

		//自己這個節點的編號
		long long m_lNumber;

		//記錄自己的狀態
		NodeState m_NodeState;

		//進入的時間點, 離開的時間點, 暫停的時間點
		TimeType::time_point m_EnterTp, m_LeaveTp, mHangTp;

		//記錄待在這個Node的時間
		std::chrono::milliseconds	m_stayms;
	};
}