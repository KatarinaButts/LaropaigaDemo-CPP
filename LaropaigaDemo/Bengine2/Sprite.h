#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

#include <string>

namespace Bengine2 {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();

	private:
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		//vertex buffer object id
		GLuint m_vboID;	//note: GLuint is the same as unsigned int but is GUARANTEED to be 32 bits

		GLTexture m_texture;

	};


}