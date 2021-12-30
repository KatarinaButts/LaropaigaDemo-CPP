#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include <vector>

namespace Bengine2 {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph {	//our single sprite instance, we have this because we want to be able to sort glyphs by textures
	public:
		Glyph() {};	//default Glyph constructor
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color, float angle);

		GLuint texture;
		float depth;
		
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);

	};

	//stores the information about what it needs to render (the specific offset into the vertex buffer object)
	class RenderBatch {
	public:
		//setting up our RenderBatch
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
			numVertices(NumVertices), texture(Texture) {

		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;

	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void dispose();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);	//set to the default value of GlyphSortType::TEXTURE
		void end();
		
		//adds a glyph to the spritebatch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color); //destRect is basically position x,y and dimensions z (width), w (height)
		
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle); //destRect is basically position x,y and dimensions z (width), w (height)

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir); //destRect is basically position x,y and dimensions z (width), w (height)

		
		
		void renderBatch();

	private:
		void createRenderBatches();

		//create our vertex array object
		void createVertexArray();
		//our funtion for sorting the Glyphs
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);


		GLuint m_vbo;
		GLuint m_vao;

		GlyphSortType m_sortType;

		//if we use a pointer, we only have to sort 4 or 8 byte quantities of pointers rather than sorting the amount of bytes stored in the struct
		//this array is for sorting purposes
		std::vector<Glyph*> m_glyphPointers;

		//actual glyphs
		//all of these will be right next to each other in memory, so it helps with cache performance
		std::vector<Glyph> m_glyphs;
		std::vector<RenderBatch> m_renderBatches;
	};

}