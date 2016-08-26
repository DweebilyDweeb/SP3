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
		if (mit.first->second->getNum() < 99)
			mit.first->second->setNum(mit.first->second->getNum() + item->getNum());
	}
}

Attributes ItemManager::removeItem(string vname, int val)
{
	map<string, Item*>::iterator mit;
	mit = itemMap.find(vname);
	Attributes temp;

	if (mit != itemMap.end()) {
		if ((*mit).second->getNum() - val < 0) {
			int tempNo = (*mit).second->getNum();
			(*mit).second->setNum(0);
			temp = (*mit).second->getAttributes() * tempNo;
		}
		else {
			(*mit).second->setNum((*mit).second->getNum() - val);
			temp = (*mit).second->getAttributes() * val;
		}
	}
	return temp;
}
void ItemManager::resetItem()
{
	for (map<string, Item*>::iterator mit = itemMap.begin(); mit != itemMap.end(); ++mit) {
		(*mit).second->setNum(0);
	}
}
/***********************************************/
