#include "Food.h"



Food::Food()
{
}


Food::~Food()
{
}

void Food::init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int healValue, int sellValue) {
	m_position = pos;
	
	m_itemCode = itemCode;
	m_itemType = 1;	//food
	m_itemName = itemName;
	m_textureID = textureID;

	m_healValue = healValue;
	m_sellValue = sellValue;
	m_buyValue = sellValue * 5;

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
}