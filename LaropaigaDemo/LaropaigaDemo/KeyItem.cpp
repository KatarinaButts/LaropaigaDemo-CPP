#include "KeyItem.h"



KeyItem::KeyItem()
{
}


KeyItem::~KeyItem()
{
}

void KeyItem::init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID) {
	m_position = pos;

	m_itemCode = itemCode;
	m_itemType = 4;		//key item
	m_itemName = itemName;
	m_textureID = textureID;

	m_sellValue = -1;	//not for sale
	m_buyValue = -1;	//not available to purchase;

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

}