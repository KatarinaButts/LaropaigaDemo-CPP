#include "Box.h"

Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions,
	Bengine2::GLTexture texture, Bengine2::ColorRGBA8 color, bool fixedRotation,
	bool isDynamic, float angle, /* = 0.0f*/
	glm::vec4 uvRect /*= glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)*/) {
	m_dimensions = dimensions;
	m_texture = texture;
	m_color = color;
	m_uvRect = uvRect;
	m_fixedRotation = fixedRotation;
	m_isDynamic = isDynamic;

	//make the body
	b2BodyDef bodyDef;
	if (isDynamic) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.angle = angle;
	m_body = world->CreateBody(&bodyDef);

	//create the shape
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	//create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_fixture = m_body->CreateFixture(&fixtureDef);

}

void Box::destroy(b2World* world) {
	world->DestroyBody(m_body);
}

void Box::draw(Bengine2::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;	//xPos
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;	//yPos
	destRect.z = m_dimensions.x;	//width
	destRect.w = m_dimensions.y;	//height
	spriteBatch.draw(destRect, m_uvRect, m_texture.id, 0.0f, m_color, m_body->GetAngle());
}