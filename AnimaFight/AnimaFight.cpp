// AnimaFight.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "../Core/Item/Item.h"

int main()
{
	AnimeFight::Item item1(AnimeFight::System), item2(AnimeFight::Player);

	//item2���ݦbitem1�W
	bool bRet = item1 << item2;

	//item1���ݨ�item2�W(�|����, �]��item1�Oitem2��owner)
	bool bRet2 = item1 >> item2;

	return 0;
}

