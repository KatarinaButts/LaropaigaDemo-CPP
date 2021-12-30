#pragma once
#include "GLTexture.h"
#include <string>

namespace Bengine2 {

	//static class
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);	//fileName/path

	};

}