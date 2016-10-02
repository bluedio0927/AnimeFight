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

		// ���oItem�ثe��Type
		const ItemType& GetType();

		// ���o�ثe�֦���Item
		const MapItem& GetMapAdjunctItew();

		// ���o�ثe����Item�֦��ۤv
		Item *const & GetOwner();

		// �P�_�o��Item�O���O�ۤv���ݪ�Item
		bool IsMyAdjunct(const Item *In_pAdjunctItem);

		// �P�_�o��Item�O���O�֦��ۤv��Item
		bool IsMyOwner(const Item *In_pOwnerItem) const;

		// ���O����Item�֦��ۤv
		bool ChangeOwner(Item *In_pOwntItem);

		// �^�ǳo��Item�ण����ݨ�ۤv
		bool CanAppend(const Item *In_pAdjunctItem);

		// �^�ǳo��Item�ण��֦��ۤv
		bool CanOwn(const Item *In_pOwntItem);

		// �O��Item���ݦۤv ��Operator
		bool operator <<(Item& sourceitem);

		// �ۤv���ݨ�O��Item��Operator
		bool operator >>(Item& targetitem);

		/*	���󥻨����ĪG�i�H�мg�b�o�Ө禡�̭��C
			�ѼƴN�O�A�o��Functor�ү�v�T���Ҧ�Item�C
			�w�q�W�N�O����o��Functor�N�O����o��Item������"�ĪG"�C
		*/
		virtual bool operator()(long long Reserved, std::vector<Item *> &pVecItem)
		{
			return true;
		}

	protected:
		// �W�[�ۤv���ݪ�Item
		bool AddAdjunct(Item *In_pAdjunctItem);

		// �����ۤv���ݪ�Item
		bool RemoveAdjunct(Item *In_pAdjunctItem);

		// ����CanAppend�ɷ|�I�s���禡, �D�n�O���~�Ӫ������W�[�ۤv�P�_������
		virtual bool SelfDoCanAppend(const Item *In_pAdjunctItem)
		{
			return true;
		}

		// ����CanOwn�ɷ|�I�s���禡, �D�n�O���~�Ӫ������W�[�ۤv�P�_������
		virtual bool SelfDoCanOwn(const Item *In_pOwntItem)
		{
			return true;
		}

		// ChangeOwner�p�G���\, �����|�۰ʩI�s��Function(���~�Ӫ�Item�мg)
		virtual void SelfDoChangeOwner(Item *In_pBeforeItem, Item *In_pAfterItem)
		{}

	private:
		ItemType m_eItemType;

		// ����Item�֦��o��Item, �Y��nullptr�N�N��S�H�֦���(�q�`�OSystem)
		Item	*m_pOwner;

		// ����Item���ݦۤv�A��K�ۤv�o��Item�nDelete�ɡA�@�ֲ����Ҧ����ݦۤv���F��C
		MapItem m_mapAdjunctItem;
	};
}
#endif // !_ANIMAFIGHT_ITEM_H

