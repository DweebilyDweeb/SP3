#ifndef ITEM_MANAGER_H_
#define ITEM_MANAGER_H_
#define GRAVITY -10

#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include "Attributes.h"
#include "SingletonTemplate.h"
#include "Vector3.h"

using namespace std;

class Item
{
public:
	Item(string vname = "", int vnum = 0);
	virtual ~Item() {};

	//virtual void setAttributes(float vit, float carb, float hyd, float fat, float pro) = 0;
	void setName(const string& name);
	void setNum(const int& num); 

	string getName() const; 
	int getNum() const; 

	virtual void setPosition(const Vector3& pos) = 0;
	virtual Vector3 getPosition() = 0;
	virtual Attributes getAttributes() = 0;
	virtual void Update(const double& deltaTime) = 0;

protected:
	Vector3 position;
	string name;
	int num;
};

class ItemManager : public Singleton<ItemManager>
{
	friend class Singleton<ItemManager>;

public:
	~ItemManager(){
	};

	void addItem(Item* item);
	Item* removeItem(string vname, int val);
	
	map<string, Item*>itemMap;
private:
	ItemManager() {};
};

class Inventory : public Singleton<Inventory>
{
	friend class Singleton<Inventory>;

public:
	~Inventory(){
	};
	vector<Item*> inventoryVec;
	void setSize(const Vector3& size) {
		this->size = size;
	}
	Vector3 getSize() const {
		return size;
	}
	void setPos(const Vector3& pos) {
		this->pos = pos;
	}
	Vector3 getPos() const {
		return pos;
	}

private:
	Vector3 size;
	Vector3 pos;
};


class Milk : public Item
{
public:
	Milk(int vnum = 1) {
		setName("Milk");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Milk() {};
	virtual Attributes getAttributes() {
		return attri;
	}

	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

private:
	Attributes attri;
};

class Egg : public Item
{
public:
	Egg(int vnum = 1) {
		setName("Egg");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Egg() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

private:
	Attributes attri;
};

class Apple : public Item
{
public:
	Apple(int vnum = 1) {
		setName("Apple");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Apple() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {
		position.y += (float)GRAVITY * deltaTime;
	}
private:
	Attributes attri;
};

#endif