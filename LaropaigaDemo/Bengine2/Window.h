#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>


namespace Bengine2 {

	//INVISIBLE =    1
	//FULLSCREEN =  10
	//BORDERLESS = 100
	enum windowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };	//they're in hexadecimal

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void swapBuffer();

		int getScreenWidth() {return m_screenWidth; }
		int getScreenHeight() {return m_screenHeight; }


	private:
		SDL_Window * _sdlWindow;
		int m_screenWidth;
		int m_screenHeight;
	};

}