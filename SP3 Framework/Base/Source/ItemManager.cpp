#include "ItemManager.h"

/******************** ITEM *********************/
Item::Item(string vname, int vnum) :
name(vname),
num(vnum),
position(Vector3(0, 0, 0))
{

}

void Item::setName(const string& name) {
	this->name = name;
}

void Item::setNum(const int& num) {
	this->num = num;
}

string Item::getName() const {
	return name;
}

int Item::getNum() const {
	return num;
}
/***********************************************/


/**************** ITEM MANAGER *****************/
void ItemManager::addItem(Item* item) {
	pair<map<string, Item*>::iterator, bool> mit;
	mit = itemMap.insert(pair<string, Item*>(item->getName(), item));
	if (mit.second == false) {
		mit.first->second->setNum(mit.first->second->getNum() + item->getNum());
	}
}

Item* ItemManager::removeItem(string vname, int val)
{
	map<string, Item*>::iterator mit;
	mit = itemMap.find(vname);

	Item* temp;
	temp = nullptr;

	if (mit != itemMap.end()) {
		temp->setName(vname);
		if ((*mit).second->getNum() - val < 0) {
			temp->setNum((*mit).second->getNum());
		}
		else
			temp->setNum(val);

		(*mit).second->setNum((*mit).second->getNum() - val);
		if ((*mit).second->getNum() <= 0) {
			itemMap.erase(mit++);
		}
	}
	return temp;
}
/***********************************************/
