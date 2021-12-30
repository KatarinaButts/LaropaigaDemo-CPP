#pragma once

#include <Bengine2/SpriteBatch.h>
#include <Bengine2/TileSheet.h>
#include "Item.h"

class Chest
{
public:
	Chest();
	~Chest();

	void init(const glm::vec2& position, int itemCode, int itemAmount, int chestType);
	void init(const glm::vec2& position, Item drop, int itemAmount, int chestType);

	//void draw(Bengine2::SpriteBatch& spriteBatch);		//do later?? or do we leave this for GamePlayScreen/Level to create? Probably the second option

	Item calcDrop(int itemCode);

	//setter
	bool setInteracting() { if (m_playerInteracting == false) { m_playerInteracting = true; } }

	//getters
	glm::vec2 getPos() const { return m_position; }
	Item getDrop() const { return m_drop; }
	int getItemAmount() const { return m_itemAmount; }


private:
	Bengine2::ColorRGBA8 m_color;
	Bengine2::TileSheet m_texture;

	glm::vec2 m_drawDims;
	glm::vec2 m_position;

	Item m_drop;

	int m_frames;
	int m_itemAmount;
	int m_chestType;

	bool m_playerInteracting;

};

