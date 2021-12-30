#pragma once

#include <glm/glm.hpp>
#include <Bengine2/SpriteBatch.h>
#include <Bengine2/TileSheet.h>
#include <Bengine2/InputManager.h>
#include <Bengine2/DebugRenderer.h>
#include "Item.h"

enum class PlayerState { STANDING, RUNNING_HORIZONTAL, RUNNING_VERTICAL, RUNNING_DIAGONAL, INTERACT, USE_ITEM, IN_AIR };

//const float AGENT_WIDTH = 64.0f;

class Player {
public:
	void init(float speed, const glm::vec2& position/*, Bengine2::InputManager* inputManager*/, const glm::vec2& drawDims,
		const glm::vec2& collisionDims, Bengine2::ColorRGBA8 color);

	void update(Bengine2::InputManager& inputManager, std::vector<std::vector<int>> levelLayout, float deltaTime);

	void draw(Bengine2::SpriteBatch& spriteBatch);

	//void drawDebug(Bengine2::DebugRenderer& debugRenderer);

	bool collideWithLevel(std::vector<std::vector<int>> levelLayout);

	void resetPlayerSteps();

	//getters
    glm::vec2 getPosition() const { return m_position; }
	const glm::vec2& getDrawDims() const { return m_drawDims; }
	const glm::vec2& getCollisionDims() const { return m_collisionDims; }
	const Bengine2::ColorRGBA8& getColor() const { return m_color; }
	float getPlayerSteps() { return m_playerSteps; }

protected:
	void checkTilePosition(std::vector<std::vector<int>> levelLayout,
		std::vector<glm::vec2>& collideTilePositions,
		float x,
		float y);

	void collideWithTile(glm::vec2 tilePos);

	glm::vec2 m_drawDims;
	glm::vec2 m_collisionDims;
	int m_playerHeight;
	int m_playerWidth;
	glm::vec2 m_position;

	Bengine2::ColorRGBA8 m_color;
	Bengine2::TileSheet m_texture;
	//Bengine2::InputManager* m_inputManager;

	PlayerState m_moveState = PlayerState::STANDING;
	float m_animTime = 0.0f;

	int m_frames;

	float m_speed;
	float m_health;
	float m_playerSteps;

	int m_direction = 7;	 //1 through 8, 1 (facing west) going clockwise to 8 (facing south-west)
	bool m_onGround = false;
	bool m_punching = false;
	bool m_interact = false;

};

