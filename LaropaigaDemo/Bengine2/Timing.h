#pragma once

namespace Bengine2 {

	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);
		void setMaxFPS(float maxFPS);

		void beginFrame();	//aka FpsLimiter::begin()

		//returns the current fps
		float end();


	private:

		void calculateFPS();
		float m_maxFPS;
		float m_fps;
		float m_frameTime;
		unsigned int m_startTicks;

	};

}