#pragma once
#include <Bengine2/IMainGame.h>
#include "MainMenuScreen.h"
#include "GamePlayScreen.h"

class App : public Bengine2::IMainGame {

public:
	App();
	~App();

	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;

private:

	std::unique_ptr<MainMenuScreen> m_mainMenuScreen = nullptr;
	std::unique_ptr<GamePlayScreen> m_gameplayScreen = nullptr;

};

