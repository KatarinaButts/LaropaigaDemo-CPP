#pragma once

#include "Item.h"


class Weapon : public Item {	//inherits from Item

public:
	Weapon();
	~Weapon();



	void init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int damageValue, int damageType, int sellValue);

	//getters
	int getDamageValue() const { return m_damageValue; }
	int getDamageType() const { return m_damageType; }


private:
	int m_damageValue;
	int m_damageType;

};

