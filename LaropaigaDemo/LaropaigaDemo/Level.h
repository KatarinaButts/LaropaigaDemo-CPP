#pragma once

#include <string>
#include <vector>

#include <Bengine2/SpriteBatch.h>
#include "Chest.h"
const int TILE_SIZE = 64;

class Level {

public:
	Level(const std::string& fileName);
	~Level();

	void draw();

	void calcLevelType(int levelTypeInt);

	void ProcessTile(int tileInt, glm::vec4 destRect, glm::vec4 uvRect, Bengine2::ColorRGBA8 color, int x, int y);

	void addChest(glm::vec2 pos, int itemCode, int itemAmount, int chestType);

	//getters
	int getLevelWidth() const { return m_levelData[0].size(); }
	int getLevelHeight()const { return m_levelData.size(); }
	const std::vector<std::string>& getLevelData() const { return m_levelData; }
	const std::vector<std::vector<int>> getLevelLayout() const{return  m_levelLayout; }

	glm::vec2 getPlayerStartPos() const { return m_playerStartPos; }
	int getLevelType() const { return m_levelType; }
	bool getIsDungeonLevel() const { return m_dungeonLevel; }
	const std::vector<Chest>& getChests() const { return m_chests; }	//makes sure no one can change the vector, but we're returning the actual vector

private:
	std::vector<std::string> m_levelData;
	std::vector<std::vector<int>> m_levelLayout;
	
	Bengine2::SpriteBatch m_spriteBatch;
	std::vector<Chest> m_chests;
	//std::vector<Item> m_items;
	//std::vector<Agent> m_agents;

	glm::vec2 m_playerStartPos;
	int m_levelType;
	bool m_dungeonLevel;
};

