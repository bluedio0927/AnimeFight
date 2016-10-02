// AnimaFight.cpp : 定義主控台應用程式的進入點。
//

#include "../Core/Item/Item.h"

int main()
{
	AnimeFight::Item item1(AnimeFight::System), item2(AnimeFight::Player);

	//item2附屬在item1上
	bool bRet = item1 << item2;

	//item1附屬到item2上(會失敗, 因為item1是item2的owner)
	bool bRet2 = item1 >> item2;

	return 0;
}

