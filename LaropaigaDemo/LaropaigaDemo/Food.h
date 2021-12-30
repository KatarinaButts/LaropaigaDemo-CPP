#pragma once

#include "Item.h"

class Food : public Item {	//inherits from Item
public:
	Food();
	virtual ~Food();	//because this is a class where other classes inherit from, we need to assign it as "virtual" so it knows to also call the polymorphized destructors



	void init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int healValue, int sellValue);

	//getters
	int getHealValue() const { return m_healValue; }


private:
	int m_healValue;

};

