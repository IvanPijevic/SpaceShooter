#ifndef TIMING_H
#define TIMING_H

#include <chrono>
#include <Windows.h>

class Timing
{
public:
	Timing(int desiredFPS);

	float getDeltaTime();
	void reset();

private:
	std::chrono::high_resolution_clock::time_point m_prevTime;

	const float m_desiredFrameRate;

};

class FpsLimiter
{
public:
	void init(float maxFPS);

	void begin();
	float end();

	void setMaxFPS(float maxFPS);

private:
	void calculateFPS();
	float epochTime();

private:
	float m_fps;
	float m_maxFPS;

	//Frame time start/end
	float m_startTime;
	float m_frameTime;

};

#endif  //TIMING_H