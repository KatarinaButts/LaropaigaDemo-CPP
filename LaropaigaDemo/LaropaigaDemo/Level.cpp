#include "Level.h"

#include <Bengine2/BengineErrors.h>
#include <fstream>
#include <iostream>
#include <Bengine2/ResourceManager.h>

#include "pugixml.hpp"

Level::Level(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName);

	if (file.fail()) {
		Bengine2::fatalError("Failed to open " + fileName);
	}

	// Throw away the first string in tmp
	std::string tmp;
	file >> tmp >> m_levelType;
	std::getline(file, tmp); // Throw away the rest of the first line
	calcLevelType(m_levelType);

	// Read the level data
	while (std::getline(file, tmp)) {
		m_levelData.emplace_back(tmp);
	}

	char tile;
	int i;
	std::string str;

	// process the level
	for (int y = 0; y < m_levelData.size(); y++) {
		std::vector<int> row;
		for (int x = 0; x < m_levelData[y].size(); x++) {
			tile = m_levelData[y][x];
			if (tile != ',') {
				str.push_back(tile);
			}
			else {
				i = std::stoi(str);
				//std::cout << "strTest changed to an int with std::stoi: " << i << "\n";
				row.push_back(i);
				str = "";
				//file.ignore();	//ignore the comma
			}
		}
		m_levelLayout.push_back(row);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Bengine2::ColorRGBA8 whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	//Render all the tiles
	std::cout << "*****Rendering Tiles*****\n";

	for (int i = 0; i < m_levelLayout.size(); i++) {
		for (int j = 0; j < m_levelLayout[i].size(); j++) {
			int currTile = m_levelLayout[i][j];
			//std::cout << m_levelLayout[x][y] << " ";
			std::cout << currTile << " ";
			// Get dest rect
			glm::vec4 destRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			ProcessTile(currTile, destRect, uvRect, whiteColor, i, j);
		}
		std::cout << std::endl;
	}
	//check for levelObjects and add these to level
	//!!!change these to actual game objects later?

	//!!!need to change this mess!!!, level needs to know its own file when it's created, but this is to test
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("test_level_objects.xml");
	std::cout << "Load result: " << result.description() << std::endl;

	//test vars
	int chestPosX;
	int chestPosY;
	glm::vec2 chestPos;
	int chestType;
	int chestDrop;
	int chestDropAmt;
	//std::string chestName;

	for (pugi::xml_node chest = doc.child("Objects").child("Chest"); chest; chest = chest.next_sibling("Chest")) {
		//chestName = chest.first_attribute().value();
		//std::cout << "chestName test: " << chestName << "\n";
		//std::cout << "Chest Name: " << chest.first_attribute().name() << " = " << chest.first_attribute().value() << "\n";
		//grab x pos
		std::cout << "posx: " << chest.child_value("posx") << "\n";
		chestPosX = std::stoi(chest.child_value("posx"));
		std::cout << "chestPosX = " << chestPosX << std::endl;
		//grab y pos
		std::cout << "posy: " << chest.child_value("posy") << "\n";
		chestPosY = std::stoi(chest.child_value("posy"));
		std::cout << "chestPosY = " << chestPosY << std::endl;
		chestPos.x = chestPosX;
		chestPos.y = chestPosY;
		//grab chest type
		std::cout << "type: " << chest.child_value("type") << "\n";
		chestType = std::stoi(chest.child_value("type"));
		std::cout << "chestType = " << chestType << std::endl;
		//grab chest drop
		std::cout << "Chest Drop: " << chest.child_value("drop") << "\n";
		chestDrop = std::stoi(chest.child_value("drop"));
		std::cout << "chestDrop = " << chestDrop << std::endl;
		//grab chest drop amount
		std::cout << "Drop Amount: " << chest.child_value("drop_amount") << "\n";
		chestDropAmt = std::stoi(chest.child_value("drop_amount"));
		std::cout << "chestDropAmt = " << chestDropAmt << std::endl;

		addChest(chestPos, chestDrop, chestDropAmt, chestType);
	}



	std::cout << "*****Done Rendering Tiles*****\n";



	m_spriteBatch.end();

}

Level::~Level() {
	//Empty
}

void Level::draw() {
	m_spriteBatch.renderBatch();
}

void Level::calcLevelType(int levelTypeInt) {
	switch (levelTypeInt) {
	case 0:
		m_dungeonLevel = false;
		break;
	case 1:
		m_dungeonLevel = true;
		std::cout << "this is a dungeon level/n";
		break;
	default:
		m_dungeonLevel = false;
	}
}

void Level::ProcessTile(int tileInt, glm::vec4 destRect, glm::vec4 uvRect, Bengine2::ColorRGBA8 color, int x, int y) {
	// Process the tile
	switch (tileInt) {
	case 0:	//air
		break;
	case 1:	//player
		m_levelLayout[x][y] = 0; // So we dont collide with a 1
		m_playerStartPos.x = x * TILE_SIZE;
		m_playerStartPos.y = y * TILE_SIZE;
		break;
	case 2:	//fir tree bottom
		m_spriteBatch.draw(destRect,
			uvRect,
			Bengine2::ResourceManager::getTexture("Textures/firTreeBottom.png").id,
			0.0f,
			color);
		break;
	case 3:	//fir tree top
		m_spriteBatch.draw(destRect,
			uvRect,
			Bengine2::ResourceManager::getTexture("Textures/firTreeTop.png").id,
			0.0f,
			color);
		break;
	default:
		std::printf("Unexpected symbol %d at (%d,%d)", tileInt, x, y);
		break;
	}
}

void Level::addChest(glm::vec2 pos, int itemCode, int itemAmount, int chestType) {


}