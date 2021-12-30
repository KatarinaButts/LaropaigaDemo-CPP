#include "GLSLProgram.h"
#include "BengineErrors.h"
#include "IOManager.h"

#include <fstream>
#include <vector>

namespace Bengine2 {

	//initialization list
	GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {

	}


	GLSLProgram::~GLSLProgram() {

	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
		std::string vertSource;
		std::string fragSource;

		IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
		IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);
		
		compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
	}

	void GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource) {
		//vertex and fragment shaders are successfully compiled
		//now time to link them together into a program
		//get a program object
		m_programID = glCreateProgram();	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		//error checking
		if (m_vertexShaderID == 0) {
			fatalError("Vertex shader failed to be created!");
		}
		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		//error checking
		if (m_fragmentShaderID == 0) {
			fatalError("Fragment shader failed to be created!");
		}

		compileShader(vertexSource, "Vertex Shader", m_vertexShaderID);
		compileShader(fragmentSource, "Fragment Shader", m_fragmentShaderID);
	}


	//combines the shaders into one program
	void GLSLProgram::linkShaders() {

		//attach our shaders to our program
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		//link our program
		glLinkProgram(m_programID);

		//note the different functions here: glGetProgram* instead of glGetShader*
		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//the maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);



			//we don't need the program anymore
			glDeleteProgram(m_programID);
			//make sure we don't let shaders loose anywhere
			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);

			//prints out the errorLog info
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		//detaches shaders after a successful link (ALWAYS DO THIS!!!!!)
		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);

		//and then you can safely delete them so the space can be used later for something else
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

	}

	void GLSLProgram::addAttribute(const std::string& attributeName) {
		glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str()); //m_numAttributes starts at 0 and then it'll add one after the line of code runs
	}


	//can be used to set the time variable in our case
	GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {	//name of UniformLocation, 
		GLint location = glGetUniformLocation(m_programID, uniformName.c_str());	//programID, 
		if (location == GL_INVALID_INDEX) {
			fatalError("Uniform " + uniformName + " not found in shader!");
		}
		return location;
	}



	void GLSLProgram::use() {
		glUseProgram(m_programID);
		//enables the use of the attribute at the current index
		for (int i = 0; i < m_numAttributes; i++) {	//for ours it just runs once because we have one attribute
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse() {
		glUseProgram(0);	//same thing as using no program
		//loops through and disables the use of the attribute at the current index
		for (int i = 0; i < m_numAttributes; i++) {	//for ours it just runs once because we have one attribute
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::dispose() {
		if (m_programID) {	//is != 0
			glDeleteProgram(m_programID);
		}
	}


	void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id) {

		//initialize the shader source
		glShaderSource(id, 1, &source, nullptr);	//the id, the amount of strings (we just put all of ours into a single string above), pointer to an array of "c_str"s, pointer to an array of integers for the length of each string (we just have one string, so we just label it as "nullptr" and are ok with that)

		//compile the shader
		glCompileShader(id);

		//error checking for vertex shader
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);	//returns a true if it works
		//if it returns a false though:
		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			//provide the infolog in whatever manner you deem best
			//exit with a failure
			glDeleteShader(id); //makes sure the shader doesn't go anywhere else


			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + name + " failed to compile!");
		}
	}
}