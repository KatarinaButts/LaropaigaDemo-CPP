#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bengine2 {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

		void offsetPosition(const glm::vec2& offset) { m_position += offset; m_needsMatrixUpdate = true; }
		void offsetScale(float offset) { m_scale += offset; if (m_scale < 0.001f) m_scale = 0.001f; m_needsMatrixUpdate = true; }

		//setters
		void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needsMatrixUpdate = true; }
		void setScale(float newScale) { m_scale = newScale; m_needsMatrixUpdate = true; }

		//getters
		glm::vec2& getPosition() { return m_position; }
		float getScale() { return m_scale; }
		glm::mat4& getCameraMatrix() { return m_cameraMatrix; }
		float getAspectRatio() const { return (float)m_screenWidth / (float)m_screenHeight; }


	private:
		int m_screenWidth;
		int m_screenHeight;

		bool m_needsMatrixUpdate;	//checks if we need to update the matrix
		float m_scale;				//scaling factor

		glm::vec2 m_position;				//uses two floats	(x, y)
		glm::mat4 m_cameraMatrix;			//4x4 matrix (our orthographic matrix for positioning [ie our identity matrix])
		glm::mat4 m_orthoMatrix;


	};
}
