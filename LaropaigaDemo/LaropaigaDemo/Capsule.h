#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <Bengine2/DebugRenderer.h>

class Capsule
{
public:
	void init(const glm::vec2& position,
		const glm::vec2& dimensions,
		bool fixedRotation);

	/*
	void destroy();

	void drawDebug(Bengine2::DebugRenderer& debugRenderer);

	//b2Body* getBody() const { return m_body; }
	//b2Fixture* getFixture(int index) const { return m_fixtures[index]; }
	const glm::vec2& getDimesions() const { return m_dimesions; }

private:
	//b2Body* m_body = nullptr;
	//b2Fixture* m_fixtures[3];
	glm::vec2 m_dimesions;


	*/
};

