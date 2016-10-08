#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "../Core/Time/TimeLine.h"

namespace TimeLineTest
{
	static void RunTimeLine(AnimeFight::TimeLine &Line)
	{
		using namespace std::chrono;
		auto tpNowTimet = system_clock::to_time_t(system_clock::now());
		//std::cout << "Enter TimeLine" << std::endl << std::ctime(&tpNowTimet);
		Line.Enter();

		int i(0);
		while (!Line.IsEnd())
		{
			tpNowTimet = system_clock::to_time_t(system_clock::now());
			std::cout << "GoNext TimeLine Node=" << ++i << std::endl << std::ctime(&tpNowTimet);
			std::cout << "Wait Next Node....  ";
			int iRet = Line.Next();
			std::cout <<  "Result="<< iRet << std::endl;
		}

		std::cout << "Leave TimeLine" << std::endl;
	}

	void TimeLineTest()
	{
		AnimeFight::TimeLine Line(3);
		for (size_t i = 1; i < Line.GetTimeNodeNums(); ++i)
			Line.SetTimeNodeStayTimeout(i, (i-1)*5000);

		std::cout << "Start RunTimeLineThread" << std::endl;
		auto RunTimeLineThread = new std::thread(std::bind(&RunTimeLine, std::ref(Line)));
		
		int input(0);
		do
		{
			std::cout << "1.Hang\n2.Keep\n3.GoNext\n5566.Exist\nKey:";
			std::cin >> input;
			switch (input)
			{
			case 1:
				Line.PushCMD(AnimeFight::TimeLine::Hang);
				break;
			case 2:
				Line.PushCMD(AnimeFight::TimeLine::Keep);
				break;
			case 3:
				Line.PushCMD(AnimeFight::TimeLine::GoNext);
				break;
			default:
				break;
			}
		} while (input != 5566 && !Line.IsEnd());
		Line.Cancel();
		RunTimeLineThread->join();
		std::cout << "Leave RunTimeLineThread" << std::endl;
		delete RunTimeLineThread;
		std::cin >> input;
	}
};