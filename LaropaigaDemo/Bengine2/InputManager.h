#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace Bengine2{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		//returns true if the key is held down
		bool isKeyDown(unsigned int keyID);

		//returns true if the key was just pressed
		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }	//we set it as a constant function, because it will never change anything in the class
	
	private:
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keymap;
		std::unordered_map<unsigned int, bool> m_previousKeymap;

		glm::vec2 m_mouseCoords;

	};

}