#include "Window.h"
#include "BengineErrors.h"

namespace Bengine2 {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

		Uint32 flags = SDL_WINDOW_OPENGL;

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr) {
			fatalError("SDL Window could not be created!");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}

		GLenum error = glewInit();
		//GLEW_OK returns a 0 (aka if we didn't initialize GLEW)
		if (error != GLEW_OK) {
			fatalError("Could not initialize glew!");
		}

		//lets you check the OpenGL version
		printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		//sets background color every time you call "glClear(GL_COLOR_BUFFER_BIT)"
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//sets VSYNC (0 is off, 1 is on)
		SDL_GL_SetSwapInterval(0);

		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//standard alpha blending

		return 0;

	}

	void Window::swapBuffer() {
		SDL_GL_SwapWindow(_sdlWindow);

	}

}