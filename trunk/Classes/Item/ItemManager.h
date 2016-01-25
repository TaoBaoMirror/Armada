/********************************************************************
	created:	2016/01/24
	created:	24:1:2016   10:19
	filename: 	E:\Armada\Classes\Item\ItemManager.h
	file path:	E:\Armada\Classes\Item
	file base:	ItemManager
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef ItemManager_h__
#define ItemManager_h__

#include <list>

class Item;
class ItemManager
{
public:
	static ItemManager*	GetInstance();
	static Item*	CreateItem(int itemType);
	//
	void ClearAllItems();
	void Init();
	void Free();
	//
	void AddItem(Item* item);
	void RemoveItem(Item* item,bool clearup = true);
	void UpdateItems(float dt);

protected:
	ItemManager();
	virtual ~ItemManager();
	//
	std::list<Item*>	mItems;
private:
};
#endif // ItemManager_h__
