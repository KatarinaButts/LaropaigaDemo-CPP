#pragma once
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Bengine2/SpriteBatch.h>

const float ITEM_WIDTH = 60.0f;
const float ITEM_RADIUS = ITEM_WIDTH / 2.0f;

//doing a forward declaration, so we don't have to include the header files for these classes (prevents us from having circular includes)
class Food;
class Weapon;
class Armor;
class KeyItem;

class Item {
public:
	Item();
	virtual ~Item();	//because this is a class where other classes inherit from, we need to assign it as "virtual" so it knows to also call the polymorphized destructors

	void init(glm::vec2 pos, int itemCode, std::string itemName, GLuint textureID, int sellValue);

	void draw(Bengine2::SpriteBatch& m_spriteBatch);	//want to pass a reference to instead of a copy of the spritebatch

	//getters
	int getItemCode() const { return m_itemCode; }
	int getItemType() const { return m_itemType; }
	int getSellValue() const { return m_sellValue; }
	int getBuyValue() const { return m_buyValue; }
	std::string getItemName() const { return m_itemName; }
	glm::vec2& getPosition() { return m_position; }		//we had to change this in the original code because camera issues


protected:
	int m_itemCode;		//code used to calculate item information
	int m_itemType;		//0 = general, 1 = food, 2 = weapon, 3 = armor, 4 = key item,
	std::string m_itemName;
	glm::vec2 m_position;
	Bengine2::ColorRGBA8 m_color;
	GLuint m_textureID;
	int m_sellValue;
	int m_buyValue;
};

