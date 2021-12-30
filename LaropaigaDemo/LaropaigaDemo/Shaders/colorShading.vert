#version 130
//The vertex shader operates on each vertex

//input data from the vbo. Each vertex is 2 floats in vec2 vertexPosition
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

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

	fragmentUV = vec2(vertexUV.x, 1.0-vertexUV.y);
}