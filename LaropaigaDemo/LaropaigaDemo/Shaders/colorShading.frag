#version 130
//the fragment shader operates on each pixel in a given polygon

//our input colors
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//this is the 3 component float vector that gets outputted to the screen for each pixel
out vec4 color;

//uniform variable creation (These are used to communicate with your vertex or fragment shader from an "outside" souce)
uniform sampler2D mySampler; //sampler is the keyword used for textures in GL (we're using sampler2D because we're using a 2D sampler; easy enough)

void main() {

	//texture function gets the texture from the sampler 
	vec4 textureColor = texture(mySampler, fragmentUV);	//texture parameters: sampler we want to get the color from, the UV coordinates (i.e. texture coordinates [U is basically the X direction (from 0 to 1), Y is basically the Y direction (also from 0 to 1)])

	//color blending example (multiplication tends to look pretty good)
	//note: fragmentColor is white (like multiplying by 1), but we want it to be variable in case we want to change our sprite's color on command
	//color = textureColor * fragmentColor;


	//makes interesting colors based on time and position
	//developer note: cos(x) returns a number between -1 and 1.
	//To convert it into the range 0 to 1, you simply do (cos(x) + 1.0) * 0.5
	
	//***the below line is the code we started with***
	//color = fragmentColor.r * textureColor;											//alpha pos color
	
	//***the below line is the code we switched to***
	color = fragmentColor * textureColor;
	
	/*   color = fragmentColor + vec4(1.0 * (cos(time)+1.0) * 0.5,			//cos(time) = number between -1 and 1 [for red: we're adding one to make it a number between 1 and 2  and then dividing it by 2 to make it a number between 0 and 1]
								1.0 * (cos(time+2.0) + 1.0) * 0.5, 		//green
								1.0 * (sin(time+1.0) + 1.0) * 0.5,		//blue
								0.0);									//aplha
	*/

}