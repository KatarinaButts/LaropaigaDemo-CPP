#include "Player.h"
#include <Bengine2/ResourceManager.h>
#include <SDL/SDL.h>
#include "Level.h"
#include <algorithm>
#include <iostream>


void Player::init(float speed, const glm::vec2& position/*, Bengine2::InputManager* inputManager*/, const glm::vec2& drawDims,
	const glm::vec2& collisionDims, Bengine2::ColorRGBA8 color) {
	m_speed = speed;
	m_position = position;
	//m_inputManager = inputManager;
	m_drawDims = drawDims;
	m_collisionDims = collisionDims;
	m_color = color;
	
	m_playerWidth = m_collisionDims.x;
	m_playerHeight = m_collisionDims.y;
	//std::cout << "m_playerWidth: " << m_playerWidth;
	//std::cout << "m_playerHeight: " << m_playerHeight;

	m_playerSteps = 0;


	Bengine2::GLTexture texture = Bengine2::ResourceManager::getTexture("Assets/witch_sprite_sheet2.png");

	//m_texture.init(texture, glm::ivec2(10, 2));	size for blue_ninja
	m_texture.init(texture, glm::ivec2(4, 4));	//size for test witch player
}

void Player::update(Bengine2::InputManager& inputManager, std::vector<std::vector<int>> levelLayout, float deltaTime) {
	float MAX_SPEED = 10.0f;
	//std::cout << "updating player";

	if (inputManager.isKeyDown(SDLK_a) && inputManager.isKeyDown(SDLK_w)) {			//north-west
		//std::cout << "pressed a && w";

		m_position.x += -MAX_SPEED * deltaTime;
		m_position.y += MAX_SPEED * deltaTime;

		m_direction = 2;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_d) && inputManager.isKeyDown(SDLK_w)) {	//north-east
		//std::cout << "pressed d && w";

		m_position.x += MAX_SPEED * deltaTime;
		m_position.y += MAX_SPEED * deltaTime;

		m_direction = 4;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_a) && inputManager.isKeyDown(SDLK_s)) {	//south-west
		//std::cout << "pressed a && s";
		
		m_position.x += -MAX_SPEED * deltaTime;
		m_position.y += -MAX_SPEED * deltaTime;

		m_direction = 8;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_d) && inputManager.isKeyDown(SDLK_s)) {	//south-east
		//std::cout << "pressed d && s";

		m_position.x += MAX_SPEED * deltaTime;
		m_position.y += -MAX_SPEED * deltaTime;

		m_direction = 6;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_a)) {				//west
		//std::cout << "pressed a";

		m_position.x += -MAX_SPEED * deltaTime;
		m_position.y += 0.0f * deltaTime;

		m_direction = 1;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_d)) {				//east
		//std::cout << "pressed d";

		m_position.x += MAX_SPEED * deltaTime;
		m_position.y += 0.0f * deltaTime;

		m_direction = 5;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_w)) {				//north
		//std::cout << "pressed w";
		
		m_position.x += 0.0f * deltaTime;
		m_position.y += MAX_SPEED * deltaTime;

		m_direction = 3;
		m_playerSteps += 0.05f;
	}
	else if (inputManager.isKeyDown(SDLK_s)) {				//south
		//std::cout << "pressed s";
		
		m_position.x += 0.0f * deltaTime;
		m_position.y += -MAX_SPEED * deltaTime;

		m_direction = 7;
		m_playerSteps += 0.05f;
	}
	else {
		//apply damping
		//body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.01f, body->GetLinearVelocity().y * 0.01f));	//!!might need to fix this later, was: body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.95f, body->GetLinearVelocity().y));
		//std::cout << "else test";
	}

	//check for interact
	if (inputManager.isKeyPressed(SDLK_SPACE)) {
		//m_punching = true;
		std::cout << "ineract \n";
	}

	//limit max speed
	//float MAX_SPEED = 10.0f;

	glm::vec2 centerPosition = m_position + (glm::vec2(m_collisionDims) * 0.5f);

	collideWithLevel(levelLayout);

}

void Player::draw(Bengine2::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	//std::cout << "drawing Player";

	destRect.x = m_position.x;	//xPos
	destRect.y = m_position.y;	//yPos
	destRect.z = m_drawDims.x;	//width
	destRect.w = m_drawDims.y;	//height

	//std::cout << "destRect.x: " << destRect.x;
	//std::cout << "destRect.y: " << destRect.y;
	//std::cout << "destRect.z: " << m_drawDims.x;
	//std::cout << "destRect.w: " << m_drawDims.y;

	int tileIndex = 12;	//default is looking south
	int currTile = tileIndex;
	int numTiles = 1;	//default amount of tiles

	float animSpeed = 0.2f;

	//calculate animation for witch_sprite_sheet
	//check diagonals first
	if (/*(abs(velocity.x) > 1.0f && abs(velocity.y) > 1.0f) &&((velocity.x < 0 && velocity.y > 0) &&*/ m_direction == 2) {
		//north-west
		//std::cout << "north-west animation\n";
		numTiles = 4;
		tileIndex = 4;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_DIAGONAL) {
			m_moveState = PlayerState::RUNNING_DIAGONAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*(abs(velocity.x) > 1.0f && abs(velocity.y)) > 1.0f && ((velocity.x > 0 && velocity.y > 0) &&*/ m_direction == 4) {
		//north-east	//!!!need to update once we have diagonal sprites
		//std::cout << "north-east animation\n";
		numTiles = 4;
		tileIndex = 4;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_DIAGONAL) {
			m_moveState = PlayerState::RUNNING_DIAGONAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*(abs(velocity.x) > 1.0f && abs(velocity.y) > 1.0f) && ((velocity.x < 0 && velocity.y < 0) &&*/ m_direction == 8) {
		//south-west
		//std::cout << "south-west animation\n";
		numTiles = 4;
		tileIndex = 12;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_DIAGONAL) {
			m_moveState = PlayerState::RUNNING_DIAGONAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*(abs(velocity.x) > 1.0f && abs(velocity.y) > 1.0f) && ((velocity.x > 0 && velocity.y < 0) && */m_direction == 6) {
		//south-east
		//std::cout << "south-east animation\n";
		numTiles = 4;
		tileIndex = 12;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_DIAGONAL) {
			m_moveState = PlayerState::RUNNING_DIAGONAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*abs(velocity.x) > 1.0f && ((velocity.x > 0 &&*/ m_direction == 5 || /*(velocity.x < 0 &&*/ m_direction == 1) {			//check horizontals and verticals
	//running horizontal
		//std::cout << "running horizontal animation\n";
		numTiles = 4;
		tileIndex = 8;
		currTile = tileIndex;
		//animSpeed = abs(velocity.x) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_HORIZONTAL) {
			m_moveState = PlayerState::RUNNING_HORIZONTAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*abs(velocity.y) > 1.0f && (velocity.y > 0 && */m_direction == 3) {
		//running northwards
		//std::cout << "running northwards animation\n";
		numTiles = 4;
		tileIndex = 4;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_VERTICAL) {
			m_moveState = PlayerState::RUNNING_VERTICAL;
			m_animTime = 0.0f;
		}
	}
	else if (/*abs(velocity.y) > 1.0f && (velocity.y < 0 && */m_direction == 7) {
		//running southwards
		//std::cout << "running southwards animation\n";
		numTiles = 4;
		tileIndex = 12;
		currTile = tileIndex;
		//animSpeed = abs(velocity.y) * 0.01f;

		animSpeed = abs(m_speed) * 0.01f;
		if (m_moveState != PlayerState::RUNNING_VERTICAL) {
			m_moveState = PlayerState::RUNNING_VERTICAL;
			m_animTime = 0.0f;
		}
	}
	else {	//standing still
		//std::cout << "standing still animation";
		//numTiles = 1;	//number of tiles in our animation
		//tileIndex = 12;	//top-left tile
		//tileIndex = currTile;
		m_moveState = PlayerState::STANDING;
	}

	/*
	//calculate animation for blue_ninja
	if (m_onGround) {

		if (m_punching) {
			numTiles = 4;
			tileIndex = 1;
			if (m_moveState != PlayerState::INTERACT) {
				m_moveState = PlayerState::INTERACT;
				m_animTime = 0.0f;
			}

		}
		else if (abs(velocity.x) > 1.0f && ((velocity.x > 0 && m_direction > 0) || (velocity.x < 0 && m_direction < 0))) {	//running
			numTiles = 6;
			tileIndex = 10;
			animSpeed = abs(velocity.x) * 0.03f;
			if (m_moveState != PlayerState::RUNNING_HORIZONTAL) {
				m_moveState = PlayerState::RUNNING_HORIZONTAL;
				m_animTime = 0.0f;
			}
		}
		else {	//standing still
			numTiles = 1;	//number of tiles in our animation
			tileIndex = 0;	//bottom-left tile
			m_moveState = PlayerState::STANDING;
		}
	}
	else {
		//in the air
		if (m_punching) {
			numTiles = 1;
			tileIndex = 18;
			animSpeed *= 0.25f;
			if (m_moveState != PlayerState::INTERACT) {
				m_moveState = PlayerState::INTERACT;
				m_animTime = 0.0f;
			}
		}
		else if (abs(velocity.x) > 10.0f) {
			numTiles = 1;
			tileIndex = 10;
			m_moveState = PlayerState::IN_AIR;
		}
		else if (velocity.y <= 0.0f) {	//falling
			numTiles = 1;
			tileIndex = 17;
			m_moveState = PlayerState::IN_AIR;
		}
		else {	//rising
			numTiles = 1;
			tileIndex = 16;
			m_moveState = PlayerState::IN_AIR;
		}
	}

	*/






	//increment animation time
	m_animTime += animSpeed;

	//check for punch end
	/*
	if (m_animTime > numTiles) {
		m_punching = false;
	}
	*/

	//apply animation
	tileIndex = tileIndex + (int)m_animTime % numTiles;

	//get the uv coordinates from the tile index
	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

	//check horizontal direction
	if (m_direction == 5) {
		uvRect.x += 1.0f / m_texture.dims.x;	//grabs the next tile
		uvRect.z *= -1;							//causes us to grab the backwards version of the tile behind us
	}


	//draw the sprite
	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color);
}

bool Player::collideWithLevel(std::vector<std::vector<int>> levelLayout) {

	std::vector<glm::vec2> collideTilePositions;

	// Check the four corners
	// First corner
	checkTilePosition(levelLayout,
		collideTilePositions,
		m_position.x,
		m_position.y);
	// Second Corner
	checkTilePosition(levelLayout,
		collideTilePositions,
		m_position.x + m_collisionDims.x,
		m_position.y);

	// Third Corner
	checkTilePosition(levelLayout,
		collideTilePositions,
		m_position.x,
		m_position.y + m_collisionDims.y);

	// Fourth Corner
	checkTilePosition(levelLayout,
		collideTilePositions,
		m_position.x + m_collisionDims.x,
		m_position.y + m_collisionDims.y);

	// Check if there was no collision
	if (collideTilePositions.size() == 0) {
		return false;
	}

	// Do the collision
	for (int i = 0; i < collideTilePositions.size(); i++) {
		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

void Player::resetPlayerSteps() {
	m_playerSteps = 0.0f;
}

void Player::checkTilePosition(std::vector<std::vector<int>> levelLayout,
	std::vector<glm::vec2>& collideTilePositions,
	float x,
	float y) {
	// Get the position of this corner in grid-space
	glm::vec2 gridPos = glm::vec2(floor(x / (float)TILE_SIZE),
		floor(y / (float)TILE_SIZE));



	// If we are outside the world, just return
	if (gridPos.x < 0 || gridPos.x >= levelLayout[0].size() ||
		gridPos.y < 0 || gridPos.y >= levelLayout.size()) {
		return;
	}

	// If this is not an air tile, we should collide with it
	if (levelLayout[gridPos.y][gridPos.x] != 0) {
		collideTilePositions.push_back(gridPos * (float)TILE_SIZE + glm::vec2((float)TILE_SIZE / 2.0f));
	}
}

// AABB (Axis Aligned Bounding Box) collision
void Player::collideWithTile(glm::vec2 tilePos) {
	
	const float TILE_RADIUS = (float)TILE_SIZE / 2.0f;
	// The minimum distance before a collision occurs
	const float HALF_PLAYER_WIDTH = m_playerWidth / 2;
	const float HALF_PLAYER_HEIGHT = m_playerHeight / 2;

	//const float MIN_DISTANCE = TILE_SIZE + m_playerWidth/2;
	const float MIN_DISTANCEX = TILE_SIZE + HALF_PLAYER_WIDTH;
	const float MIN_DISTANCEY = TILE_SIZE + HALF_PLAYER_HEIGHT;


	//!!!test
	//const float MIN_DISTANCE = TILE_SIZE + (m_playerWidth/2);


	

	//!!!test
	//const float MIN_DISTANCEX = TILE_SIZE + half_playerWidth;
	//const float MIN_DISTANCEY = TILE_SIZE + half_playerHeight;

	//std::cout << "!!! MIN_DISTANCEX: " << MIN_DISTANCE << "\n";
	//std::cout << "!!! MIN_DISTANCEY: " << MIN_DISTANCE << "\n";

	// Center position of the agent
	//glm::vec2 centerAgentPos = m_position + glm::vec2(TILE_SIZE);
	glm::vec2 centerAgentPos;
	centerAgentPos.x = m_position.x + HALF_PLAYER_WIDTH;
	centerAgentPos.y = m_position.y + HALF_PLAYER_HEIGHT;
	//std::cout << "!!! m_position: " << m_position.x << ", " << m_position.y << "\n";
	//std::cout << "!!! centerAgentPos: " << centerAgentPos.x << ", " << centerAgentPos.y << "\n";
	////std::cout << "!!! m_playerWidth: " << m_playerWidth << "\n";
	//std::cout << "!!! m_playerHeight: " << m_playerHeight << "\n";
	


	// Vector from the agent to the tile
	glm::vec2 distVec = centerAgentPos - tilePos;
	//test
	//glm::vec2 distVec;
	//distVec.x = centerAgentPos.x - m_playerWidth/2;
	//distVec.y = centerAgentPos.y - m_playerHeight / 2;

	//std::cout << "??? distVec: " << distVec.x << ", " << distVec.y << "\n";


	// Get the depth of the collision
	//float xDepth = MIN_DISTANCE - abs(distVec.x);
	//float yDepth = MIN_DISTANCE - abs(distVec.y);

	//std::cout << "xDepth: " << xDepth << "\n";
	//std::cout << "yDepth: " << yDepth << "\n";

	//!!!test
	float xDepth = MIN_DISTANCEX - abs(distVec.x);
	float yDepth = MIN_DISTANCEY - abs(distVec.y);

	//std::cout << "xDepth: " << xDepth << "\n";
	//std::cout << "yDepth: " << yDepth << "\n";

	// If both the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) {

		// Check which collision depth is less
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			// X collsion depth is smaller so we push in X direction
			//std::cout << "hit in the x dir\n";
			if (distVec.x < 0) {
				//std::cout << "hit in the opposite direction we're testing\n";
				//std::cout << "m_position.x before: " << m_position.x << "\n";
				//std::cout << "tilePos.x: " << tilePos.x << "\n";

				m_position.x -= xDepth - m_playerWidth/2 - 5;

				//std::cout << "xDepth: " << xDepth << "\n";
				//std::cout << "m_playerWidth/2: " << m_playerWidth / 2 << "\n";
				//std::cout << "xDepth - m_playerWidth/2: " << (xDepth - m_playerWidth / 2) << "\n";
				//std::cout << "m_position.x after: " << m_position.x << "\n";
				//std::cout << "stop\n";

			}
			else {
				//std::cout << "hit in the direction we're testing\n";
				//std::cout << "m_position.x before: " << m_position.x << "\n";
				//std::cout << "tilePos.x: " << tilePos.x << "\n";

				m_position.x += xDepth - m_playerWidth/2 - 5;

				
				//std::cout << "xDepth: " << xDepth << "\n";
				//std::cout << "m_playerWidth/2: " << m_playerWidth/2 << "\n";
				//std::cout << "xDepth - m_playerWidth/2: " << (xDepth - m_playerWidth/2) << "\n";
				//std::cout << "m_position.x after: " << m_position.x << "\n";
				//std::cout << "stop\n";



			}
		}
		else {
			// Y collsion depth is smaller so we push in Y direction
			if (distVec.y < 0) {
				m_position.y -= (yDepth - m_playerHeight/2);
			}
			else {
				m_position.y += (yDepth - m_playerHeight/2);
			}
		}
	}
}