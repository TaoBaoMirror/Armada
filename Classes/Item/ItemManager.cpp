#include "ItemManager.h"
#include "Item.h"
#include "ItemQuicken.h"
#include "Ship/ShipManager.h"

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{

}

ItemManager* ItemManager::GetInstance()
{
	static ItemManager T;
	return &T;
}

Item* ItemManager::CreateItem(int itemType)
{
	Item* item = nullptr;

	switch (itemType)
	{
	case 1:
		item = new ItemQuicken();
		break;
	default:
		break;
	}
	//
	return item;
}

void ItemManager::ClearAllItems()
{
	std::list<Item*>::iterator it = mItems.begin();

	while (it != mItems.end())
	{
		Item* item = *it;
		it = mItems.erase(it);
		item->removeFromParentAndCleanup(true);
		delete item;
	}
}

void ItemManager::Init()
{

}

void ItemManager::Free()
{

}

void ItemManager::AddItem(Item* item)
{
	mItems.push_back(item);
}

void ItemManager::RemoveItem(Item* item, bool clearup)
{
	if (clearup) mItems.remove(item);

	item->DestoryItem();

}

void ItemManager::UpdateItems(float dt)
{
	std::list<Item*>::iterator it = mItems.begin();

	while (it != mItems.end())
	{
		Item* item = *it;
		//
		std::map<TeamShipSeat, ShipBase*>& left_ships = ShipManager::getInstance()->GetTeamLeftShips();	
		std::map<TeamShipSeat, ShipBase*>::iterator itTeam = 
			left_ships.begin();
		for (; itTeam != left_ships.end(); ++itTeam)
		{
			ShipBase* pShip = itTeam->second;
			if (pShip != nullptr)
			{
				if (item->OnCollision(pShip))
				{
					item->DestoryItem();
				}
			}
		}
		//
		std::map<TeamShipSeat, ShipBase*>& right_ships = ShipManager::getInstance()->GetTeamRightShips();
		std::map<TeamShipSeat, ShipBase*>::iterator itEnemy = right_ships.begin();
		for (; itEnemy != right_ships.end(); ++itEnemy)
		{
			ShipBase* pShip = itEnemy->second;
			if (pShip != nullptr)
			{
				if (item->OnCollision(pShip))
				{
					item->DestoryItem();
				}
			}
		}
		//
		item->UpdateItem(dt);
		//
		if (!item->Alive())
		{
			it = mItems.erase(it);

			RemoveItem(item,false);
			
		}
		else
		{
			it++;
		}
	}
}

//

