#include "App.h"
#include <Bengine2/ScreenList.h>



App::App() {
	//Empty
}


App::~App() {
	//Empty
}

void App::onInit() {

}

void App::addScreens() {
	m_mainMenuScreen = std::make_unique<MainMenuScreen>(&m_window);
	m_gameplayScreen = std::make_unique<GamePlayScreen>(&m_window);

	m_screenList->addScreen(m_mainMenuScreen.get());
	m_screenList->addScreen(m_gameplayScreen.get());

	m_screenList->setScreen(m_mainMenuScreen->getScreenIndex());
}

void App::onExit() {

}