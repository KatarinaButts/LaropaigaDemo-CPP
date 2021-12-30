#include "Armor.h"



Armor::Armor()
{
}


Armor::~Armor()
{
}

void Armor::init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int armorValue, int sellValue) {
	m_position = pos;

	m_itemCode = itemCode;
	m_itemType = 3;	//armor
	m_itemName = itemName;
	m_textureID = textureID;

	m_armorValue = armorValue;

	m_sellValue = sellValue;
	m_buyValue = sellValue * 12;

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
}