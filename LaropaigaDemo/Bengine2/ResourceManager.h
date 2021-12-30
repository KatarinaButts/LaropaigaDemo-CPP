#pragma once
#include "TextureCache.h"
#include <string>

namespace Bengine2 {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
	private:
		static TextureCache m_textureCache;
	};

}