#version 130
//the fragment shader operates on each pixel in a given polygon

//our input colors
in vec2 fragmentPosition;
in vec4 fragmentColor;

//this is the 3 component float vector that gets outputted to the screen for each pixel
out vec4 color;

void main() {

	color = fragmentColor;
	
}