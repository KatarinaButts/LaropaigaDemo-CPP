#include "DebugRenderer.h"

const float PI = 3.14159265359f;


//in a separate namespace to avoid name collisions in other files
namespace {
	//raw string that has all of the vertex source code
	const char* VERT_SRC = R"(#version 130
//The vertex shader operates on each vertex

//input data from the vbo. Each vertex is 2 floats in vec2 vertexPosition
in vec2 vertexPosition;
in vec4 vertexColor;

out vec2 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 P;		//our orthographic projection matrix

void main() {
	//Set the x,y position on the screen
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;	//our 2d vertex position, z (which is 0.0, because 2d), and w
	
	//the z position is zero since we are in 2D
	gl_Position.z = 0.0;
	
	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;

	fragmentPosition = vertexPosition;

	fragmentColor = vertexColor;
})";

	const char* FRAG_SRC = R"(#version 130
//the fragment shader operates on each pixel in a given polygon

//our input colors
in vec2 fragmentPosition;
in vec4 fragmentColor;

//this is the 3 component float vector that gets outputted to the screen for each pixel
out vec4 color;

void main() {

	color = fragmentColor;
	
})";

}

namespace Bengine2 {
	DebugRenderer::DebugRenderer() {
		//Empty
	}


	DebugRenderer::~DebugRenderer() {
		dispose();
	}

	void DebugRenderer::init() {
		//set up shader/shader init
		m_program.compileShadersFromSource(VERT_SRC, FRAG_SRC);
		m_program.addAttribute("vertexPosition");
		m_program.addAttribute("vertexColor");
		m_program.linkShaders();

		//set up buffers
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		//bind the vertex array
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);	//index buffer for index drawing


		//set up vertex attribute pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));


		//unbind vertex arrays
		glBindVertexArray(0);

	}

	void DebugRenderer::end() {
		//vbo
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//orphan the buffer for speed
		glBufferData(GL_ARRAY_BUFFER, m_verts.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the date
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_verts.size() * sizeof(DebugVertex), m_verts.data());
		//unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//ibo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		//orphan the buffer for speed
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
		//upload the date
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());
		//unbind
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_numElements = m_indices.size();
		m_indices.clear();
		m_verts.clear();

	}

	glm::vec2 rotatePoint(glm::vec2 pos, float angle) {
		glm::vec2 newV;	//new vector
		newV.x = pos.x * cos(angle) - pos.y * sin(angle);
		newV.y = pos.x * sin(angle) + pos.y * cos(angle);
		return newV;
	}

	void DebugRenderer::drawLine(const glm::vec2& a, const glm::vec2& b, const ColorRGBA8& color) {
		int i = m_verts.size();
		m_verts.resize(m_verts.size() + 2);

		m_verts[i].position = a;
		m_verts[i].color = color;
		m_verts[i + 1].position = b;
		m_verts[i + 1].color = color;

		m_indices.push_back(i);
		m_indices.push_back(i + 1);
	}

	void DebugRenderer::drawBox(const glm::vec4& destRect, const ColorRGBA8& color, float angle) {
		int i = m_verts.size();
		m_verts.resize(m_verts.size() + 4);
		
		glm::vec2 halfDimens(destRect.z / 2.0f, destRect.w / 2.0f);

		//get points centered at origin
		//top left
		glm::vec2 tl(-halfDimens.x, halfDimens.y);
		//bottom left
		glm::vec2 bl(-halfDimens.x, -halfDimens.y);
		//bottom right
		glm::vec2 br(halfDimens.x, -halfDimens.y);
		//top right
		glm::vec2 tr(halfDimens.x, halfDimens.y);

		glm::vec2 positionOffset(destRect.x, destRect.y);

		//rotate the points, and add back our halfDimens so we go back to our normal top left position
		m_verts[i].position = rotatePoint(tl, angle) + halfDimens + positionOffset;
		m_verts[i + 1].position = rotatePoint(bl, angle) + halfDimens + positionOffset;
		m_verts[i + 2].position = rotatePoint(br, angle) + halfDimens + positionOffset;
		m_verts[i + 3].position = rotatePoint(tr, angle) + halfDimens + positionOffset;

		for (int j = i; j < i + 4; j++) {
			m_verts[j].color = color;
		}

		m_indices.reserve(m_indices.size() + 8);

		//draw a line between i and i+1
		m_indices.push_back(i);
		m_indices.push_back(i + 1);

		//draw a line between i+1 and i+2
		m_indices.push_back(i + 1);
		m_indices.push_back(i + 2);

		//draw a line between i+2 and i+3
		m_indices.push_back(i + 2);
		m_indices.push_back(i + 3);

		//draw a line between i+3 and i
		m_indices.push_back(i + 3);
		m_indices.push_back(i);

	}

	void DebugRenderer::drawCircle(const glm::vec2& center, const ColorRGBA8& color, float radius) {
		//figure out how many verts we need (better to make more for how big the object on the screen is, but 100 is a good starting point)
		static const int NUM_VERTS = 100;
		
		//set up vertices
		int start = m_verts.size();
		m_verts.resize(m_verts.size() + NUM_VERTS);

		for (int i = 0; i < NUM_VERTS; i++) {
			float angle = ((float)i / NUM_VERTS) * PI * 2.0f;
			m_verts[start + i].position.x = cos(angle) * radius + center.x;	//cos for x
			m_verts[start + i].position.y = sin(angle) * radius + center.y;	//sin for y
			m_verts[start + i].color = color;

		}

		//set up indices for indexed drawing
		m_indices.reserve(m_indices.size() + NUM_VERTS * 2);
		for (int i = 0; i < NUM_VERTS - 1; i++) {
			m_indices.push_back(start + i);
			m_indices.push_back(start + i + 1);
		}

		//end the loop (end of the circle has to be a special case)
		m_indices.push_back(start + NUM_VERTS - 1);
		m_indices.push_back(start);


	}

	void DebugRenderer::render(const glm::mat4& projectionMatrix, float lineWidth) {
		m_program.use();

		//upload the projectionMatrix
		GLint pUniform = m_program.getUniformLocation("P");
		glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

		//set the width of the line
		glLineWidth(lineWidth);

		//bind vao
		glBindVertexArray(m_vao);

		glDrawElements(GL_LINES, m_numElements, GL_UNSIGNED_INT, 0);

		//unbind vao
		glBindVertexArray(0);

		m_program.unuse();

	}

	void DebugRenderer::dispose() {
		if (m_vao) {	//is != 0
			glDeleteVertexArrays(1, &m_vao);
		}
		if (m_vbo) {	//is != 0
			glDeleteBuffers(1, &m_vbo);
		}
		if (m_ibo) {	//is != 0
			glDeleteBuffers(1, &m_ibo);
		}
		m_program.dispose();
	}
}
