#pragma once

#define NOMINMAX

#include <Bengine2/AudioEngine.h>
#include <Bengine2/Camera2D.h>
#include <Bengine2/DebugRenderer.h>
#include <Bengine2/GLSLProgram.h>
#include <Bengine2/GLTexture.h>
#include <Bengine2/GUI.h>
#include <Bengine2/IGameScreen.h>
#include <Bengine2/SpriteBatch.h>
#include <Bengine2/SpriteFont.h>
#include <Bengine2/Timing.h>
#include <Bengine2/Window.h>

#include <vector>

#include "Player.h"
#include "Level.h"

class GamePlayScreen : public Bengine2::IGameScreen {

public:
	GamePlayScreen(Bengine2::Window* window);
	~GamePlayScreen();

	//Returns the index of the next or previous screen when changing screens
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	//called at beginning and end of application
	virtual void build() override;
	virtual void destroy() override;

	//called when a screen enters or exits focus
	virtual void onEntry() override;
	virtual void onExit() override;

	//called in the main game loop
	virtual void update() override;
	virtual void draw() override;

	// Initializes the core systems
	void initSystems();

	// Initializes the level and sets up everything
	void initLevel();

	// Initializes the shaders
	void initShaders();

	// Draws the HUD
	void drawHud();

private:
	void initUI();
	void checkInput();
	void startBattle();
	void calcItem(int itemCode);

	bool onExitClicked(const CEGUI::EventArgs& e);


	Bengine2::AudioEngine m_audioEngine;

	Bengine2::DebugRenderer m_debugRenderer;
	Bengine2::GLSLProgram m_textureProgram;

	Bengine2::InputManager m_inputManager; //< Handles input

	//Bengine2::GLSLProgram m_lightProgram;
	//Bengine2::GLTexture m_texture;
	Bengine2::GUI m_gui;

	Bengine2::Camera2D m_camera;	//Main Camera
	Bengine2::Camera2D m_hudCamera;	// Hud Camera

	//Bengine2::SpriteBatch m_spriteBatch;
	Bengine2::SpriteBatch m_agentSpriteBatch;
	Bengine2::SpriteBatch m_hudSpriteBatch;

	Bengine2::SpriteFont* m_spriteFont;
	Bengine2::Window* m_window;

	// Some helpful constants.
	const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
	const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
	const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
	const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

	// Used to cap the FPS
	Bengine2::FpsLimiter fpsLimiter;
	
	float m_fps;
	float m_previousTicks;

	std::vector<Level*> m_levels; //< vector of all levels

	int m_currentLevel;

	bool m_renderDebug = false;

	Player* m_player;
	int m_numStepsUntilEvent;

	//std::unique_ptr<b2World> m_world;



};

