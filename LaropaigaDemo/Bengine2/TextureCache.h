#pragma once
#include <map>
#include "GLTexture.h"

namespace Bengine2 {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map <std::string, GLTexture> m_textureMap;
	};

}