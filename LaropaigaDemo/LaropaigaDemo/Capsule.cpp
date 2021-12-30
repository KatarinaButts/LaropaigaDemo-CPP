#include "Capsule.h"

void Capsule::init(const glm::vec2& position,
	const glm::vec2& dimensions,
	bool fixedRotation) {
	/*

	m_dimesions = dimensions;

	//make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	m_body = world->CreateBody(&bodyDef);

	//create the box
	//create the box shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, (dimensions.y - dimensions.x) / 2.0f);
	//create the box fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	m_fixtures[0] = m_body->CreateFixture(&fixtureDef);

	//create the circles
	b2CircleShape circleShape;
	circleShape.m_radius = dimensions.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = density;
	circleDef.friction = friction;

	//bottom circle
	circleShape.m_p.Set(0.0f, (-m_dimesions.y + dimensions.x) / 2.0f);
	m_fixtures[1] = m_body->CreateFixture(&circleDef);
	//top circle
	circleShape.m_p.Set(0.0f, (m_dimesions.y - dimensions.x) / 2.0f);
	m_fixtures[1] = m_body->CreateFixture(&circleDef);
	*/
}



/*


void Capsule::destroy(b2World* world) {
	if (m_body) {
		world->DestroyBody(m_body);
		m_body = nullptr;
	}
}


void Capsule::drawDebug(Bengine2::DebugRenderer& debugRenderer) {
	Bengine2::ColorRGBA8 color(255, 255, 255, 255);

	//draw box
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimesions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - (m_dimesions.y - m_dimesions.x) / 2.0f;
	destRect.z = m_dimesions.x;
	destRect.w = m_dimesions.y - m_dimesions.x;
	debugRenderer.drawBox(destRect, color, m_body->GetAngle());

	//draw circle
	debugRenderer.drawCircle(glm::vec2(destRect.x + m_dimesions.x / 2.0f, destRect.y), color, m_dimesions.x / 2.0f);	//bottom circle
	debugRenderer.drawCircle(glm::vec2(destRect.x + m_dimesions.x / 2.0f, destRect.y + destRect.w), color, m_dimesions.x / 2.0f);	//top circle

}

*/