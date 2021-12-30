#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace Bengine2 {

	Sprite::Sprite() {
		m_vboID = 0;	//always start vertex buffer objects to 0 (it's like setting things to null)
	}

	Sprite::~Sprite() {
		//free the buffer everytime the sprite is destroyed
		if (m_vboID != 0) {
			glDeleteBuffers(1, &m_vboID);	//delete 1 buffer, pointer to the buffer
		}


	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath) {
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		m_texture = ResourceManager::getTexture(texturePath);

		//generates the buffer if it hasn't been generated
		if (m_vboID == 0) {
			//allocate it to a buffer (this id)
			glGenBuffers(1, &m_vboID);	//delete 1 buffer, pointer to the buffer (each generation has a unique id)
		}
		//we need 6 vertices for a square[aka a quad]: 3 per triangle (2 will overlap)
		//make an array of floats
		Vertex vertexData[6]; //6 * 2 (x, y coordinates) [the positions are already stored in each vertice]

		//first triangle
		vertexData[0].setPosition(x + width, y + height); //x of 1st vertex (top right corner coord), y of 1st vertex (top right corner coord)
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		//setting all of the colors to the same thing for now
		for (int i = 0; i < 6; i++) {
			vertexData[i].setColor(255, 0, 255, 255);
		}

		vertexData[1].setColor(0, 0, 255, 255);	//!!!CHANGED!!! Used to be "vertexData[4].setColor(0, 0, 255, 255);"

		vertexData[4].setColor(0, 255, 0, 255);

		//bind the buffer (make this buffer active)
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID); //basic buffer type, which buffer

		//upload the data

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);	//which bound buffer to use, amount of data/size, what the data is (pointer to the data), usage (how are we gonna use this? [draw just once? many times?])

		//unbind the buffer (for good measure)
		glBindBuffer(GL_ARRAY_BUFFER, 0); //using the 0 id is the same as saying "I don't want to bind anything" (ids will ALWAYS be a positive number, so this means don't bind anything)
	}

	void Sprite::draw() {

		//bind the texture
		glBindTexture(GL_TEXTURE_2D, m_texture.id);  	//we do NOT unbind the texture, because we may need to use it again

		//current buffer active
		//bind the buffer (make this buffer active)
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID); //basic buffer type, which buffer

		

		//here's where we do the drawing


		//this actually draws our data (array of vertices)

		glDrawArrays(GL_TRIANGLES, 0, 6); //types of things, what the first element is, how many are there? (6 vertices [the vertexPointer above already knows there are two elements {x, y} for each vertice, so it will end up as 6*2])


		//disables it after we're done
		glDisableVertexAttribArray(0);	//using the 0th index [1st element in the array]
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//unbind the buffer (for good measure)
		glBindBuffer(GL_ARRAY_BUFFER, 0); //using the 0 id is the same as saying "I don't want to bind anything" (ids will ALWAYS be a positive number, so this means don't bind anything)
	}

}