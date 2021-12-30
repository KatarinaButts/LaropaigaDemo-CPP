#include "InputManager.h"

namespace Bengine2 {


	InputManager::InputManager() : m_mouseCoords(0.0f)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::update() {

		//loop through m_keymap using a for each loop, and copy it over to m_previousKeymap
		for (auto& it : m_keymap) {
			m_previousKeymap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyID) {
		m_keymap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		m_keymap[keyID] = false;
	}

	void InputManager::setMouseCoords(float x, float y) {
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;

	}


	bool InputManager::isKeyDown(unsigned int keyID) {
		//we don't want to create a key if it doesn't exist, so we need to do it manually
		auto it = m_keymap.find(keyID);
		if (it != m_keymap.end()) {
			//found the key
			return it->second;
		}
		else {
			//didn't find the key
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		//check if key was pressed this frame and wasn't pressed last frame
		bool isPressed;
		if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
			isPressed = true;
		}
		else {
			isPressed = false;
		}




		return isPressed;
	}

	bool InputManager::wasKeyDown(unsigned int keyID) {
		//we don't want to create a key if it doesn't exist, so we need to do it manually
		auto it = m_previousKeymap.find(keyID);
		if (it != m_previousKeymap.end()) {
			//found the key
			return it->second;
		}
		else {
			//didn't find the key
			return false;
		}
	}


}