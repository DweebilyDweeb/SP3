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

	virtual void Update(const double& deltaTime){};

private:
	Attributes attri;
};


class Meat : public Item
{
public:
	Meat(int vnum = 1) {
		setName("Meat");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Meat() {};
	virtual Attributes getAttributes() {
		return attri;
	}

	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime){};

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

	virtual void Update(const double& deltaTime){};

private:
	Attributes attri;
};

class Water : public Item
{
public:
	Water(int vnum = 1) {
		setName("Water");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Water() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime){};

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
	};

private:
	Attributes attri;
};


class Fish : public Item
{
public:
	Fish(int vnum = 1) {
		setName("Fish");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Fish() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {};

private:
	Attributes attri;
};

class Cabbage : public Item
{
public:
	Cabbage(int vnum = 1) {
		setName("Cabbage");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Cabbage() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {};

private:
	Attributes attri;
};

class Potato : public Item
{
public:
	Potato(int vnum = 1) {
		setName("Potato");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Potato() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {};

private:
	Attributes attri;
};

class Corn : public Item
{
public:
	Corn(int vnum = 1) {
		setName("Corn");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Corn() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {};

private:
	Attributes attri;
};

class Carrot : public Item
{
public:
	Carrot(int vnum = 1) {
		setName("Carrot");
		setNum(vnum);
		attri.setAttributes(8, 2, 2, 2, 2);
	};

	virtual ~Carrot() {};
	virtual Attributes getAttributes() {
		return attri;
	}
	virtual void setPosition(const Vector3& pos) {
		position = pos;
	}

	virtual Vector3 getPosition() {
		return position;
	}

	virtual void Update(const double& deltaTime) {};

private:
	Attributes attri;
};

class ItemManager : public Singleton<ItemManager>
{
	friend class Singleton<ItemManager>;

public:
	~ItemManager(){
	};

	void addItem(Item* item);
	Attributes removeItem(string vname, int val);

	map<string, Item*>itemMap;
	void resetItem();
private:
	ItemManager() {
		addItem(new Milk(10));
		addItem(new Meat(10));
		addItem(new Egg(10));
		addItem(new Water(10));
		addItem(new Apple(98));
		addItem(new Fish(10));
		addItem(new Cabbage(10));
		addItem(new Potato(10));
		addItem(new Corn(10));
		addItem(new Carrot(10));
	};
   
};

#endif