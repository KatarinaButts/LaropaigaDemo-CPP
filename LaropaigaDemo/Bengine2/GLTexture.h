#pragma once
#include <GL/glew.h>
#include <string>

namespace Bengine2 {

	struct GLTexture {
		std::string filePath = "";
		GLuint id;
		int width;
		int height;
	};
}