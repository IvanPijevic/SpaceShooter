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

#endif  //TIMING_H