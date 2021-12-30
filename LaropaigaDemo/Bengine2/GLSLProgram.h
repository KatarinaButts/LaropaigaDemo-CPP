#pragma once

#include <string>
#include <GL/glew.h>

//Lets us operate the OpenGL Shading Languange

namespace Bengine2 {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		//links the two shaders together in a format OpenGL can use so it can perform everything at once
		//the two strings specify the file path for the fragment and vertex shaders
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

		void linkShaders();

		void addAttribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);	//name of UniformLocation, 

		void use();
		void unuse();

		void dispose();

	private:
		int m_numAttributes;

		void compileShader(const char* source, const std::string& name, GLuint id);

		GLuint m_programID;	//refers to the finished product
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;



	};

}