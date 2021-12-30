#include <Bengine2/BengineErrors.h>
#include <Bengine2/IMainGame.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "pugixml.hpp"

int main(int argc, char** argv) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("test_level_objects.xml");
	std::cout << "Load result: " << result.description() << std::endl;

	//test vars
	int chestPosX;
	int chestPosY;
	int chestDrop;
	int chestDropAmt;

	//This helps a lot with xml traversals: https://github.com/zeux/pugixml/blob/master/docs/samples/traverse_base.cpp   &   https://github.com/zeux/pugixml/blob/master/docs/samples/xgconsole.xml

	//check for chests in the level
	//if (!m_levels[m_currentLevel]->getChestPositions().empty()) {	//if there is at least one chest in the level
		//figure out what the content(s) are from our xml objects file
		std::string chestName;

		//add them
		for (pugi::xml_node chest = doc.child("Objects").child("Chest"); chest; chest = chest.next_sibling("Chest")) {
			chestName = chest.first_attribute().value();
			std::cout << "chestName test: " << chestName << "\n";
			std::cout << "Chest Name: " << chest.first_attribute().name() << " = " << chest.first_attribute().value() << "\n";
			//grab x pos
			std::cout << "posx: " << chest.child_value("posx") << "\n";
			chestPosX = std::stoi(chest.child_value("posx"));
			std::cout << "chestPosX = " << chestPosX << std::endl;
			//grab y pos
			std::cout << "posy: " << chest.child_value("posy") << "\n";
			chestPosY = std::stoi(chest.child_value("posy"));
			std::cout << "chestPosY = " << chestPosY << std::endl;
			//grab chest drop
			std::cout << "Chest Drop: " << chest.child_value("drop") << "\n";
			chestDrop = std::stoi(chest.child_value("drop"));
			std::cout << "chestDrop = " << chestDrop << std::endl;
			//grab chest drop amount
			std::cout << "Drop Amount: " << chest.child_value("drop_amount") << "\n";
			chestDropAmt = std::stoi(chest.child_value("drop_amount"));
			std::cout << "chestDropAmt = " << chestDropAmt << std::endl;
		}
	//}



	/*
	pugi::xml_document doc;
	if (!doc.load_file("test_level_objects.xml")) {
		std::cout << "doc was not found, throwing error" << std::endl;
		return -1;
	}
		
	pugi::xml_node objects = doc.child("Objects");

	// tag::data[]
	for (pugi::xml_node objects = objects.child("Chest"); objects; objects = objects.next_sibling("Chest"))
	{
		std::cout << "Chest posx " << objects.child("posx") << std::endl;
		std::cout << "Chest posy " << objects.child("posy") << std::endl;
		std::cout << "Chest drop " << objects.child("drop") << std::endl;
		std::cout << "Chest drop_amount " << objects.child("drop_amount") << std::endl;
	}
	// end::data[]
	*/


	//***atoi/stoi test***
	/*
	std::vector<std::string> m_levelData;
	std::vector<std::vector<int>> m_testVect;

	std::cout << "***atoi test***\n";

	std::ifstream file;
	file.open("Levels/atoiTest1.txt");

	if (file.fail()) {
		Bengine2::fatalError("Failed to open file\n");
	}
	std::string tmp;
	while (std::getline(file, tmp)) {
		m_levelData.emplace_back(tmp);
	}

	char tile;
	int i;

	int sizeY = 7;
	int sizeX = 2;
	int strStartPos = 0;
	std::string strTest;

	for (int y = 0; y < m_levelData.size(); y++) {
		std::vector<int> row;
		for (int x = 0; x < m_levelData[y].size(); x++) {
			tile = m_levelData[y][x];
			if (tile != ',') {
				strTest.push_back(tile);
				std::cout <<"strTest = " << strTest << "\n";
			}
			else {
				i = std::stoi(strTest);
				std::cout << "strTest changed to an int with std::stoi: " << i << "\n";
				row.push_back(i);

				strTest = "";
				//file.ignore();	//ignore the comma
			}
		}
		m_testVect.push_back(row);
	}

	std::cout << "*****Printing Vector*****\n";

	for (int i = 0; i < m_testVect.size(); i++) {
		for (int j = 0; j < m_testVect[i].size(); j++) {
			std::cout << m_testVect[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "*****Done Printing Vector*****\n";

	*/

	return 0;
}