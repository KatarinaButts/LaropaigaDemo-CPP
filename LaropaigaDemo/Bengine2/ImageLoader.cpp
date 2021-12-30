#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "BengineErrors.h"

namespace Bengine2 {


	GLTexture ImageLoader::loadPNG(std::string filePath) {
		GLTexture texture = {};		//the curly braces just initialize everything to 0

		//load the PNG with picoPNG
		std::vector<unsigned char> out;
		std::vector<unsigned char> in;	//we're going to fill this with what we get from our IOManager (our image loaded in)

		unsigned long width, height;

		//loads the data
		//error checking + how to use IOManager's readFileToBuffer
		if (IOManager::readFileToBuffer(filePath, in) == false) {
			fatalError("Failed to load PNG file to buffer!");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0) {
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		//generates texture object
		glGenTextures(1, &(texture.id));	//turns texture id from 0 to a unique id for that specific texture
		//binds the texture
		glBindTexture(GL_TEXTURE_2D, texture.id); //type of texture, id
		//upload the image data to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		//setting parameters so we can tell GL how to treat the texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//how it will filter the pixels based on the size of the texture (linear interpolation is best in most cases)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //mipmapping is when we take a texture and progressively make it smaller and smaller and sample it there (the pixels can blend together and make a much better far away image or a better smaller resolution image_

		glGenerateMipmap(GL_TEXTURE_2D);

		//unbinding textures (for good measure)
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;
		texture.filePath = filePath;

		//return a copy of the texture data
		return texture;
	}

}