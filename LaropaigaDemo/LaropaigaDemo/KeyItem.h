#pragma once

#include "Item.h"

class KeyItem : public Item {

public:
	KeyItem();
	~KeyItem();

	void init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID);



};

