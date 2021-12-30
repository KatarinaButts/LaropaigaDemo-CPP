#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int damageValue, int damageType, int sellValue) {

	m_position = pos;

	m_itemCode = itemCode;
	m_itemType = 2;	//weapon
	m_itemName = itemName;
	m_textureID = textureID;

	m_damageValue = damageValue;
	m_damageType = damageType;

	m_sellValue = sellValue;
	m_buyValue = sellValue * 15;

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
}