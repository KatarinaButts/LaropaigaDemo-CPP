#pragma once

#include "Bengine2.h"
#include "Window.h"
#include "InputManager.h"
#include <memory>

namespace Bengine2 {
	class ScreenList;
	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreens() = 0;
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event& evnt);

		const float getFps() const { return m_fps; }

		InputManager inputManager;

	protected:
		//custom update function
		virtual void update();
		//custom render function
		virtual void draw();

		bool init();
		bool initSystems();

		std::unique_ptr<ScreenList> m_screenList = nullptr;
		IGameScreen* m_currentScreen = nullptr;
		bool m_isRunning = false;
		float m_fps = 0.0f;
		Window m_window;
	};

}


