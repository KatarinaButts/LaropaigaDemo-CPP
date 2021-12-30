#include "Chest.h"



Chest::Chest() {

}


Chest::~Chest() {

}

void Chest::init(const glm::vec2& position, int itemCode, int itemAmount, int chestType) {
	m_position = position;
	m_drop = calcDrop(itemCode);
	m_itemAmount = itemAmount;
	m_chestType = chestType;
}

void Chest::init(const glm::vec2& position, Item drop, int itemAmount, int chestType) {
	m_position = position;
	m_drop = drop;
	m_itemAmount = itemAmount;
	m_chestType = chestType;
}

/*
void Chest::draw(Bengine2::SpriteBatch& spriteBatch) {

}
*/

Item Chest::calcDrop(int itemCode) {
	Item itemToDrop;
	switch (itemCode) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			//https://github.com/Barnold1953/GraphicsTutorials/search?q=m_textureID
			itemToDrop.init(m_position, itemCode, "Stick", /*need GLuint textureID here*/, 1);
			break;
	}
	//!!!need to work on Level.cpp after this to work out the kinks with Chest/other game object creation
}