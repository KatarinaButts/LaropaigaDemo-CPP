#include "Camera2D.h"


namespace Bengine2 {
	Camera2D::Camera2D() : m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),	//sets orthomatrix to the identity matrix (for good practice)
		m_scale(1.0f),
		m_needsMatrixUpdate(true),
		m_screenWidth(500),
		m_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight) {
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		//builds our orthoMatrix (we only need to build this when our screen width/height changes)
		m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);	//parameters are the dimensions of our window (left is left side of our window, right is screenwidth (in float form), etc)

	}


	void Camera2D::update() {
		if (m_needsMatrixUpdate) {
			//***camera translation***
			//this also makes sure the camera is centered on the image/screen/m_position
			glm::vec3 translate(-m_position.x + m_screenWidth/2, -m_position.y + m_screenHeight/2, 0.0f);	//parameters are position x, position y, and position z (since we are not doing 3 dimensions, we set this to 0.0f)
			//use the m_orthoMatrix to calculate our m_cameraMatrix
			//a translation is a transformation which moves your objects around
			//in this case, we're moving our entire viewport (everything on the screen basically)
			//we move these in the opposite direction of our position (ie when we go to the right, everything goes to the left)
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);	//parameters are the matrix we are translating, the glm vector which encodes the translation
			
			//***camera scale***															
			//the vector for the scale
			glm::vec3 scale(m_scale, m_scale, 0.0f);	//uses the m_scale variable (when it's 1.0f, we're just multiplying it by 1 (so it'll be the normal scale), 0.5f would be zoomed out by 2x, and 2.0f would be zoomed in, etc.)
			//now we scale the matrix (using the identity matrix)
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			
			m_needsMatrixUpdate = false;
		}


	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {	//we want 0,0 to be in the middle of our game world
		//invert Y direction
		screenCoords.y = m_screenHeight - screenCoords.y;

		// make it so that 0, 0 is the center
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);

		//scale the coordinates (change coordinates based on the scale/how far zoomed in or out you are)
		screenCoords /= m_scale;

		//translate with the camera position
		screenCoords += m_position;

		return screenCoords;
	}

	//simple AABB test to see if a box is in the camera view
	bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimensions) {
		glm::vec2 scaledScreenDimensions = glm::vec2(m_screenWidth, m_screenHeight)/ m_scale;



		//dimensions and scaledScreenDimensions would be using the diameter sizes, so we need to divide  by 2 to get the radius
		const float MIN_DISTANCE_X = dimensions.x/2.0f + scaledScreenDimensions.x /2.0f;
		const float MIN_DISTANCE_Y = dimensions.y/2.0f + scaledScreenDimensions.y /2.0f;


		//center position of the parameters
		glm::vec2 centerPos = position + dimensions/2.0f;
		//center position of the camera
		glm::vec2 centerCameraPos = m_position;
		//vector from the object/character to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);


		if (xDepth > 0 && yDepth > 0) {
			//we have a collision
			return true;
		}
		else {
			return false;
		}

	}


}