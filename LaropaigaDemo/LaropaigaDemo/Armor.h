#pragma once

#include "Item.h"

class Armor : public Item {	//inherits from Item

public:
	Armor();
	~Armor();

	void init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int armorValue, int sellValue);

	//getters
	int getArmorValue() const { return m_armorValue; }

private:
	int m_armorValue;

};

