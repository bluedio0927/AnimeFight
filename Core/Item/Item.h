#ifndef _ANIMEFIGHT_ITEM_H
#define _ANIMEFIGHT_ITEM_H

#include <map>
#include <vector>

#include "ItemDefine.h"

namespace AnimeFight
{
	class Item
	{
	public:
		using MapItem = std::map<long long, Item *>;

	public:
		Item(ItemType In_Type, Item	*pOwner = nullptr);
		virtual ~Item();

		// 取得Item目前的Type
		const ItemType& GetType();

		// 取得目前擁有的Item
		const MapItem& GetMapAdjunctItew();

		// 取得目前那個Item擁有自己
		Item *const & GetOwner();

		// 判斷這個Item是不是自己附屬的Item
		bool IsMyAdjunct(const Item *In_pAdjunctItem);

		// 判斷這個Item是不是擁有自己的Item
		bool IsMyOwner(const Item *In_pOwnerItem) const;

		// 更改是那個Item擁有自己
		bool ChangeOwner(Item *In_pOwntItem);

		// 回傳這個Item能不能附屬到自己
		bool CanAppend(const Item *In_pAdjunctItem);

		// 回傳這個Item能不能擁有自己
		bool CanOwn(const Item *In_pOwntItem);

		// 別的Item附屬自己 的Operator
		bool operator <<(Item& sourceitem);

		// 自己附屬到別的Item的Operator
		bool operator >>(Item& targetitem);

		/*	物件本身的效果可以覆寫在這個函式裡面。
			參數就是你這個Functor所能影響的所有Item。
			定義上就是執行這個Functor就是執行這個Item本身的"效果"。
		*/
		virtual bool operator()(long long Reserved, std::vector<Item *> &pVecItem)
		{
			return true;
		}

	protected:
		// 增加自己附屬的Item
		bool AddAdjunct(Item *In_pAdjunctItem);

		// 移除自己附屬的Item
		bool RemoveAdjunct(Item *In_pAdjunctItem);

		// 執行CanAppend時會呼叫此函式, 主要是讓繼承的物件能增加自己判斷的條件
		virtual bool SelfDoCanAppend(const Item *In_pAdjunctItem)
		{
			return true;
		}

		// 執行CanOwn時會呼叫此函式, 主要是讓繼承的物件能增加自己判斷的條件
		virtual bool SelfDoCanOwn(const Item *In_pOwntItem)
		{
			return true;
		}

		// ChangeOwner如果成功, 內部會自動呼叫此Function(給繼承的Item覆寫)
		virtual void SelfDoChangeOwner(Item *In_pBeforeItem, Item *In_pAfterItem)
		{}

	private:
		ItemType m_eItemType;

		// 那個Item擁有這個Item, 若為nullptr就代表沒人擁有它(通常是System)
		Item	*m_pOwner;

		// 那些Item附屬自己，方便自己這個Item要Delete時，一併移除所有附屬自己的東西。
		MapItem m_mapAdjunctItem;
	};
}
#endif // !_ANIMAFIGHT_ITEM_H

