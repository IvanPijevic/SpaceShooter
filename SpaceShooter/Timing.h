#ifndef TIMING_H
#define TIMING_H

#include <chrono>

class Timing
{
public:
	Timing(int desiredFPS);

	double getDeltaTime();
	void reset();

private:
	std::chrono::high_resolution_clock::time_point m_prevTime;

	const float m_desiredFrameRate;

};

class FpsLimiter
{
public:
	FpsLimiter();

	void init(float maxFPS);

	void begin();
	uint32_t getMsSinceStart();
	float end();

	void setMaxFPS(float maxFPS);

private:
	void calculateFPS();

private:
	float m_fps;
	float m_maxFPS;
	float m_frameTime;
	std::chrono::high_resolution_clock::time_point m_programStartTime;

};

#endif  //TIMING_H