#include "Timing.h"

Timing::Timing(int desiredFPS) :  
	m_desiredFrameRate(1000.0f / desiredFPS),
	m_prevTime(std::chrono::high_resolution_clock::now())
{}

double Timing::getDeltaTime()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaTime = currentTime - m_prevTime;
	m_prevTime = currentTime;
	return deltaTime.count() / m_desiredFrameRate;
}
 
void Timing::reset()
{
	m_prevTime = std::chrono::high_resolution_clock::now();
}