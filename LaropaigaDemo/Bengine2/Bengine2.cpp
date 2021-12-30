#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Bengine2.h"

namespace Bengine2 {

	int init() {
		//Initializes SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//instead of having one window pane that we draw to and erase each time, we have two panes: one is being drawn to while the other is being cleared and vice versa
		//helps avoid the flickering effect
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}