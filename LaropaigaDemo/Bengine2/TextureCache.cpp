#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Bengine2 {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//lookup the texture and see if its in the map
		auto mit = m_textureMap.find(texturePath);

		//check if its not in the map
		if (mit == m_textureMap.end()) {
			//Load the texture
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//Insert it into the map
			m_textureMap.insert(make_pair(texturePath, newTexture));

			//std::cout << "Loaded Texture!\n";

			return newTexture;
		}

		//std::cout << "Used Cached Texture!\n";

		return mit->second;

	}

}