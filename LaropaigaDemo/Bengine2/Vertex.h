#pragma once

#include <GL/glew.h>

namespace Bengine2 {

	//our position struct (which ends up being 8 bytes (4 + 4))
	struct Position {	//struct of type "Position"
		float x;
		float y;
	}; // position;	//this names an instance of it to "position"   : same as having another line that says "Position position;"

	   //our color struct (each color can fit in an unsigned [255] char [or a GLubyte as seen below])
	struct ColorRGBA8 { //this ends up being 3 usable bytes plus 1 byte of padding (red, green, blue, alpha) [alpha is our transparency element]
		ColorRGBA8() : r(0), g(0), b(0), a(0) {	//default struct constructor
			//Empty
		}
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : 
			r(R), g(G), b(B), a(A) {	//default struct constructor
			
		}
		
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		float u;
		float v;
	};

	struct Vertex {
		//caution: we want the vertex structs to be a multiple of 4 bytes!!! So we need the other byte on the end
		Position position;
		ColorRGBA8 color;

		//UV texture coordinates
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}


	};

}