#pragma once
#include <Bengine2/IGameScreen.h>
#include <Bengine2/SpriteBatch.h>
#include <Bengine2/GLSLProgram.h>
#include <Bengine2/GLTexture.h>
#include <Bengine2/Camera2D.h>
#include <Bengine2/Window.h>
#include <Bengine2/DebugRenderer.h>
#include <Bengine2/GUI.h>
#include "ScreenIndices.h"
#include <vector>




class MainMenuScreen : public Bengine2::IGameScreen {
public:
	MainMenuScreen(Bengine2::Window* window);
	~MainMenuScreen();

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


private:
	void initUI();
	void checkInput();

	bool onNewGameClicked(const CEGUI::EventArgs& e);
	bool onExitClicked(const CEGUI::EventArgs& e);

	int m_nextScreenIndex = SCREEN_INDEX_GAMEPLAY;
	Bengine2::SpriteBatch m_spriteBatch;
	Bengine2::Camera2D m_camera;
	Bengine2::GLTexture m_texture;
	Bengine2::Window* m_window;
	Bengine2::GUI m_gui;
};

