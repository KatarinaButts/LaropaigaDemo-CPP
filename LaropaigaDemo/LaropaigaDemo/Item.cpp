#include "Item.h"
#include <Bengine2/ResourceManager.h>



Item::Item() {
	m_itemType = 0;
}

Item::~Item() {

}

void Item::init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int sellValue) {
	m_position = pos;
	m_itemCode = itemCode;
	m_itemName = itemName;
	m_textureID = textureID;
	m_sellValue = sellValue;

	m_itemType = 0;	//general item

	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

}

void Item::draw(Bengine2::SpriteBatch& m_spriteBatch) {

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = ITEM_WIDTH;
	destRect.w = ITEM_WIDTH;

	m_spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color);
}