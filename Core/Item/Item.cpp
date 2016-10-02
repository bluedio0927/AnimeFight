#include "Item.h"

namespace AnimeFight
{
	Item::Item(ItemType In_Type, Item *pOwner)
		:m_eItemType(In_Type), m_pOwner(pOwner)
	{
		if (m_pOwner && !m_pOwner->AddAdjunct(this))
			throw std::bad_alloc();
	}

	Item::~Item()
	{
		if (m_pOwner)
			m_pOwner->RemoveAdjunct(this);

		while (!m_mapAdjunctItem.empty())
		{
			auto pItem = m_mapAdjunctItem.begin()->second;
			delete pItem;//沒做erase map是因為Adjunct Item的解構式都會來呼叫移除
		}
	}

	const ItemType& Item::GetType()
	{
		return m_eItemType;
	}

	const Item::MapItem& Item::GetMapAdjunctItew()
	{
		return m_mapAdjunctItem;
	}

	Item *const &  Item::GetOwner()
	{
		return m_pOwner;
	}

	bool Item::IsMyAdjunct(const Item *pAdjunct)
	{
		const auto &iter = m_mapAdjunctItem.find((long long)pAdjunct);
		return iter != m_mapAdjunctItem.end();
	}

	bool Item::IsMyOwner(const Item *In_pOwnerItem) const
	{
		return m_pOwner == In_pOwnerItem;
	}

	bool Item::ChangeOwner(Item *pOwner)
	{
		bool bRet(false);
		if (CanOwn(pOwner))
		{
			if (pOwner == m_pOwner)
				bRet = true;

			if (!bRet && pOwner && pOwner->AddAdjunct(this))
			{
				if (m_pOwner)
					m_pOwner->RemoveAdjunct(this);
				SelfDoChangeOwner(m_pOwner, pOwner);
				m_pOwner = pOwner;
				bRet = true;
			}
		}
		return bRet;
	}

	bool Item::AddAdjunct(Item *pAdjunct)
	{
		if (CanAppend(pAdjunct))
		{
			m_mapAdjunctItem.emplace((long long)pAdjunct, pAdjunct);
			return true;
		}
		else
			return false;
	}

	bool Item::RemoveAdjunct(Item *pAdjunct)
	{
		if (IsMyAdjunct(pAdjunct))
		{
			m_mapAdjunctItem.erase((long long)pAdjunct);
			return true;
		}
		else
			return false;
	}

	bool Item::CanAppend(const Item *pAdjunct)
	{
		return !IsMyAdjunct(pAdjunct) && SelfDoCanAppend(pAdjunct);
	}

	bool Item::CanOwn(const Item *In_pOwnItem)
	{
		bool bRet(true);
		if (In_pOwnItem)
			bRet = !(In_pOwnItem->IsMyOwner(this));
		bRet &= SelfDoCanOwn(In_pOwnItem);
		return bRet;
	}

	bool Item::operator <<(Item& sourceitem)
	{
		return sourceitem.ChangeOwner(this);
	}

	bool Item::operator >>(Item& targetitem)
	{
		return ChangeOwner(&targetitem);
	}
}