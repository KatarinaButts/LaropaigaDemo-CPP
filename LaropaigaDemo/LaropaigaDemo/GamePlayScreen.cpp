#include "GamePlayScreen.h"
#include "ScreenIndices.h"

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include <SDL/SDL.h>

#include <Bengine2/Bengine2.h>
#include <Bengine2/BengineErrors.h>
#include <Bengine2/IMainGame.h>
#include <Bengine2/ResourceManager.h>
//#include <Bengine2/Timing.h>

//#include "pugixml.hpp"

#ifndef _DEBUG
#define PUGIXML_HEADER_ONLY
#include "pugixml.cpp"
#endif


const float PLAYER_SPEED = 10.0f;
//weird bug, follow closer to https://github.com/Barnold1953/GraphicsTutorials/blob/master/ZombieGame/MainGame.cpp
//!!!try to figure out what's going on. Nothing seems to be loading. I think we need to implement a gameloop


GamePlayScreen::GamePlayScreen(Bengine2::Window* window) : m_window(window), m_fps(0), m_player(nullptr) {
	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}


GamePlayScreen::~GamePlayScreen() {
	// Don't forget to delete the levels!
	for (int i = 0; i < m_levels.size(); i++) {
		delete m_levels[i];
	}
}

int GamePlayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GamePlayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_MAINMENU;
}

void GamePlayScreen::build() {

}

void GamePlayScreen::destroy() {

}

void GamePlayScreen::onEntry() {
	std::cout << "OnEntry\n";

	initSystems();
	initLevel();

	//Bengine2::Music music = m_audioEngine.loadMusic("Sound/XYZ.ogg");
	//music.play(-1);

	

	//initLevel();	//player is also init-ed here

	//!!! this is where player is inited here
	//init player
	//m_player.init(m_world.get(), glm::vec2(0.0f, 10.0f), glm::vec2(2.0f, 2.0f), glm::vec2(1.0f, 1.8f), Bengine2::ColorRGBA8(255, 255, 255, 255));

	initUI();

}

void GamePlayScreen::onExit() {
	m_debugRenderer.dispose();
}

void GamePlayScreen::update() {
	std::cout << "Update\n";
	// Used to cap the FPS
	//Bengine2::FpsLimiter fpsLimiter;
	//fpsLimiter.setMaxFPS(60000.0f);

	// Zoom out the camera by 3x
	//const float CAMERA_SCALE = 1.0f / 3.0f;
	//m_camera.setScale(CAMERA_SCALE);

	//m_camera.setScale(32.0f);	//32 pixels per meter

	// Start our previousTicks variable
	//float previousTicks = SDL_GetTicks();

	fpsLimiter.beginFrame();
	// Calculate the frameTime in milliseconds
	float newTicks = SDL_GetTicks();
	float frameTime = newTicks - m_previousTicks;
	m_previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
	// Get the total delta time
	float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

	std::cout << "newTicks: " << newTicks << "\n";
	std::cout << "previousTicks: " << m_previousTicks << "\n";

	std::cout << "frameTime: " << frameTime << "\n";
	std::cout << "DESIRED_FRAMETIME: " << DESIRED_FRAMETIME << "\n";
	std::cout << "frameTime / DESIRED_FRAMETIME: " << (frameTime / DESIRED_FRAMETIME) << "\n";

	//checkVictory();


	//m_inputManager.update();

	checkInput();


	int i = 0;
	std::cout << "totalDeltaTime: " << totalDeltaTime << "\n";
	std::cout << "is totalDeltaTime >  0.0f: " << (totalDeltaTime > 0.0f) << "\n";

	std::cout << "MAX_PHYSICS_STEPS: " << MAX_PHYSICS_STEPS << "\n";
	std::cout << "is i < MAX_PHYSICS_STEPS: " << (i < MAX_PHYSICS_STEPS) << "\n";

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
		std::cout << "entered while loop for updating player" << "\n";
		// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
		float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		//Update all physics here and pass in deltaTime


		m_player->update(m_game->inputManager, m_levels[m_currentLevel]->getLevelLayout(), deltaTime);

		//check if we need to battle
		if(m_player->getPlayerSteps() >= m_numStepsUntilEvent) {
			if (m_levels[m_currentLevel]->getIsDungeonLevel()) {
				startBattle();
				std::mt19937 randomEngine;
				randomEngine.seed(time(nullptr));
				std::uniform_int_distribution<int> numStepsUntilEvent(25, 100);
				m_numStepsUntilEvent = numStepsUntilEvent(randomEngine);
				std::cout << "m_numStepsUntilEvent(randomized): " << m_numStepsUntilEvent << "/n";
			}
			else {
				std::cout << "m_numStepsUntilEvent(not randomized): " << m_numStepsUntilEvent << "/n";
			}
			m_player->resetPlayerSteps();
		}

		

		//updateAgents(deltaTime);
		//updateBullets(deltaTime);
		//m_particleEngine.update(deltaTime);
		// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		totalDeltaTime -= deltaTime;
		// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		i++;
	}

	// Make sure the camera is bound to the player position
	m_camera.setPosition(m_player->getPosition());
	m_camera.update();
	m_hudCamera.update();



	

	//update the physics simulator
	//m_world->Step(1.0f / 60.0f, 6, 2);	//1.0f/framerate(which we limited to 60.0 fps)

}

void GamePlayScreen::draw() {
	std::cout << "Draw\n";
	// Set the base depth to 1.0
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	//upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	//glActiveTexture(GL_TEXTURE0);

	//camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	m_levels[m_currentLevel]->draw();

	// Begin drawing agents
	m_agentSpriteBatch.begin();

	//m_spriteBatch.begin();

	std::cout << "about to draw player";
	m_player->draw(m_agentSpriteBatch);
	std::cout << "drew player";

	// End spritebatch creation
	m_agentSpriteBatch.end();

	// Render to the screen
	m_agentSpriteBatch.renderBatch();

	// Render the heads up display
	drawHud();

	//m_spriteBatch.end();
	//m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	// Swap our buffer and draw everything to the screen!
	//m_window.swapBuffer();	???

	/*
	m_lightProgram.use();
	pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	//additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_spriteBatch.begin();

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_lightProgram.unuse();

	//reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	*/

	m_gui.draw();

	// End the frame, limit the FPS, and get the current FPS.
	m_fps = fpsLimiter.end();
	std::cout << m_fps << std::endl;
}

void GamePlayScreen::initSystems() {
	//initialize the game engine
	Bengine2::init();

	// Initialize sound, must happen after Bengine::init
	//m_audioEngine.init();		//!!!un-comment this after audioEngine is implemented and audio files have been added

	// Grey background color
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	fpsLimiter.setMaxFPS(60000.0f);
	m_previousTicks = SDL_GetTicks();


	// Set up the shaders
	initShaders();

	// Initialize our spritebatch	???
	m_agentSpriteBatch.init();
	m_hudSpriteBatch.init();

	//initialize spritebatch		???
	//m_spriteBatch.init();

	m_debugRenderer.init();

	// Initialize sprite font
	m_spriteFont = new Bengine2::SpriteFont("Fonts/rainyhearts.ttf", 64);


	//init camera
	// Zoom out the camera by 3x
	//const float CAMERA_SCALE = 1.0f / 3.0f;
	const float CAMERA_SCALE = 1.0f;



	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.setPosition(glm::vec2(m_window->getScreenWidth()/2, m_window->getScreenHeight()/2));

	m_camera.setScale(CAMERA_SCALE);
}


void GamePlayScreen::initLevel() {
	// test level
	m_levels.push_back(new Level("Levels/test_level2.txt"));
	m_currentLevel = 0;
	//float playerSpeed = PLAYER_SPEED;


	/*
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("test_level_objects.xml");
	std::cout << "Load result: " << result.description() << std::endl;

	//This helps a lot with xml traversals: https://github.com/zeux/pugixml/blob/master/docs/samples/traverse_base.cpp   &   https://github.com/zeux/pugixml/blob/master/docs/samples/xgconsole.xml

	//check for chests in the level
	if (!m_levels[m_currentLevel]->getChestPositions().empty()) {	//if there is at least one chest in the level
		//figure out what the content(s) are from our xml objects file
		std::string chestName;

		//add them
		for (pugi::xml_node chest = doc.child("objects").child("chest"); chest; chest = chest.next_sibling("chest")) {
			chestName = chest.first_attribute().value();
			std::cout << "chestName test: " << chestName << "\n";
			std::cout << "Chest Name: " << chest.first_attribute().name() << " = " << chest.first_attribute().value() << "\n";
			std::cout << "Chest Drop: " << chest.child_value("drop") << "\n";
			std::cout << "Drop Amount: " << chest.child_value("drop_amount") << "\n";
		}
	}
	//check for doors in the level
	for (pugi::xml_node door = doc.child("objects").child("door"); door; door = door.next_sibling("door")) {
		//std::cout << "chestName test: " << chestName << "\n";
		//pugi::xml_attribute attr = door.first_attribute();
		std::cout << "Door Area: " << door.child_value("area") << "\n";
		std::cout << "Door Attribute: " << door.first_attribute().name() << " = " << door.first_attribute().value() << "\n";
	}

	//pugi::xml_node chests = doc.child("objects");
	//probably want to use the iterate over child nodes here when we want to add chest objects, people objects, flower objects, etc: https://www.dreamincode.net/forums/topic/244725-how-to-parse-xml-in-c/
	//std::cout << "drop: " << doc.child("chest").child_value("drop") << "\n";	
	//pugi::xml_node door = doc.child("objects").child("door");


	std::cout << "test stop\n";
	*/

	m_player = new Player();
	//m_player->init(PLAYER_SPEED, m_levels[m_currentLevel]->getPlayerStartPos()/*, m_game->inputManager*/, glm::vec2(2.0f, 2.0f), glm::vec2(1.0f, 1.8f), Bengine2::ColorRGBA8(255, 255, 255, 255));

	//test!!!
	m_player->init(PLAYER_SPEED, m_levels[m_currentLevel]->getPlayerStartPos()/*, m_game->inputManager*/, glm::vec2(40.0f, 60.0f), glm::vec2(40.0f, 60.0f), Bengine2::ColorRGBA8(255, 255, 255, 255));

	//m_player->init(PLAYER_SPEED, , &m_inputManager, &m_camera, &m_bullets);

	//m_humans.push_back(m_player);

	if (m_levels[m_currentLevel]->getIsDungeonLevel()) {
		std::mt19937 randomEngine;
		randomEngine.seed(time(nullptr));
		std::uniform_int_distribution<int> numStepsUntilEvent(25, 100);
		m_numStepsUntilEvent = numStepsUntilEvent(randomEngine);
		std::cout << "m_numStepsUntilEvent(randomized): " << m_numStepsUntilEvent << "/n";
	}
	else {
		m_numStepsUntilEvent = 100;
		std::cout << "m_numStepsUntilEvent(not randomized): " << m_numStepsUntilEvent << "/n";
	}
	

	//std::uniform_int_distribution<int> randX(2, m_levels[m_currentLevel]->getLevelWidth() - 2);
	//std::uniform_int_distribution<int> randY(2, m_levels[m_currentLevel]->getLevelHeight() - 2);
}

void GamePlayScreen::initShaders() {
	//shader init
	//compile our texture/color shader
	m_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	//compile our light shader
	//m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	//m_lightProgram.addAttribute("vertexPosition");
	//m_lightProgram.addAttribute("vertexColor");
	//m_lightProgram.addAttribute("vertexUV");
	//m_lightProgram.linkShaders();
}

void GamePlayScreen::drawHud() {
	char buffer[256];

	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_hudSpriteBatch.begin();

	//sprintf_s(buffer, "Num Humans %d", m_humans.size());
	//sprintf_s(buffer, "Temp Hud1");
	sprintf_s(buffer, "Level Type %d", m_levels[m_currentLevel]->getLevelType());
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 0),
		glm::vec2(0.5), 0.0f, Bengine2::ColorRGBA8(255, 255, 255, 255));

	//sprintf_s(buffer, "Num Zombies %d", m_zombies.size());
	sprintf_s(buffer, "Temp Hud2");
	sprintf_s(buffer, "Num Steps %f", m_player->getPlayerSteps());
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, Bengine2::ColorRGBA8(255, 255, 255, 255));

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}



void GamePlayScreen::initUI() {
	//init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("AlfiskoSkin.scheme");
	m_gui.setFont("DejaVuSans-10");
	CEGUI::PushButton* exitButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("AlfiskoSkin/Button", glm::vec4(0.95f, 0.0f, 0.05f, 0.05f), glm::vec4(0.0f), "ExitButton"));
	exitButton->setText("X");
	//set the event to be called when we click
	exitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GamePlayScreen::onExitClicked, this));


	//CEGUI::Combobox* testCombobox = static_cast<CEGUI::Combobox*>(m_gui.createWidget("TaharezLook/Combobox", glm::vec4(0.2f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestCombobox"));
	//test
	//CEGUI::Editbox* testEditbox = static_cast<CEGUI::Editbox*>(m_gui.createWidget("AlfiskoSkin/Editbox", glm::vec4(0.4f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "TestEditBox"));


	m_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	m_gui.showMouseCursor();
	SDL_ShowCursor(0);	//turns the default cursor off, so we're only seeing one cursor on the screen
}


void GamePlayScreen::checkInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
		switch (evnt.type) {
		case SDL_QUIT:
			onExitClicked(CEGUI::EventArgs());
			break;
		}
	}
}

void GamePlayScreen::startBattle() {
	std::cout << "started a battle!/n";
	m_player->resetPlayerSteps();
}

void GamePlayScreen::calcItem(int itemCode) {
	switch (itemCode) {
	case 0:
		break;
	case 1:
		break;
	default:
		std::cout << "Item Calculating Went Wrong/n Created Stick item/n";
		break;
	}
}

bool GamePlayScreen::onExitClicked(const CEGUI::EventArgs& e) {
	//std::cout << "Im Quitting!\n";
	m_currentState = Bengine2::ScreenState::EXIT_APPLICATION;

	return true;
}

