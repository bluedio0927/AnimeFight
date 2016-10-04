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
			Hang, //停止計算節點的停留時間
			Keep, //重新計算節點的停留時間
			GoNext  //直接往下一個節點移動(需要是非Hang的狀態)
		};

		// 傳入時間軸有幾個時間節點
		TimeLine(size_t In_TimepointNums);
		virtual ~TimeLine();

		// 取得有幾個時間節點
		size_t GetTimeNodeNums();

		// 取得目前呆在那個時間節點
		size_t GetNowStayPointIndex();

		/*	設定時間點的停留時間上限, Index從0開始, In_Timeoutms設為0時代表需要收到Next CMD才會離開,	若未設定則代表立即經過這個節點.
			若回傳失敗代表Index超過節點數
		*/
		bool SetTimeNodeStayTimeout(size_t In_NodeIndex, long long In_Timeoutms);

		//  移除時間點的停留時間上限, Index從0開始
		void UnSetTimeNodeStayTimeout(size_t In_NodeIndex);

		//  丟入CMD, TimeLine自己本身有Thread會PopCMD(主要是給另一個Thread呼叫, 解決會Block住的函式)
		void PushCMD(CMDTYPE In_CMD);

		// 進入時間軸(會Block住, 直到時間節點的停留時間上限條件滿足時離開)
		void Enter();

		// 移動到下一個時間節點(會Block住, 直到時間節點的停留時間上限條件滿足時離開)
		void Next();

		// "往前移動"到某一個時間節點(會Block住, 直到時間節點的停留時間上限條件滿足時離開)
		// 若往後移動會回傳失敗, Index從0開始
		bool ForwardTo(size_t In_PointIndex);

		// 判斷是否已經執行完最後一個節點
		bool IsEnd();

		// 取消時間軸的運行與所有的Block操作
		void Cancel();

	private:
		// 給Pop CMD Thread 執行的Function..
		void DoPopCMD();

		void DoLeave();

		void GotoNode(std::unique_lock<std::mutex> &unilck, size_t Index);

		bool GetTimeNodeStayTimeout(size_t In_NodeIndex, long long &Out_Timeoutms);
		// 判斷是否已進入與離開時間軸的Flag
		bool m_bEnter, m_bLeave;

		// 目前停留的時間節點Index
		size_t m_stayTimePointIndex;

		// 擁有的所有節點
		std::vector<TimeNode>	m_vecTimeNodes;

		// 標示所有節點的是否已經滿足離開Block條件的Flag
		std::vector<bool>		m_vecTimeNodesLeaveFlag;

		// 儲存時間點的停留時間上限的MAP
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