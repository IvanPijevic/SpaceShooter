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


//FPS
FpsLimiter::FpsLimiter()
{}

void FpsLimiter::init(float maxFPS)
{
	setMaxFPS(maxFPS);
}

void FpsLimiter::begin()
{
	m_programStartTime = std::chrono::high_resolution_clock::now();

}

uint32_t FpsLimiter::getMsSinceStart()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_programStartTime);
	return static_cast<uint32_t>(duration.count());
}

float FpsLimiter::end()
{

}

void FpsLimiter::setMaxFPS(float maxFPS)
{
	m_maxFPS = maxFPS;
}