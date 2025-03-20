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
	m_startTime = epochTime();
}

//float FpsLimiter::getMsSinceStart()
//{
//	auto currentTime = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime);
//	return static_cast<float>(duration.count());
//}

float FpsLimiter::end()
{
	calculateFPS();

	float frameTime = epochTime();
	frameTime -= m_startTime;

	if (1000.0f / m_maxFPS > frameTime)
	{
		Sleep(1000.0f / m_maxFPS - frameTime);
	}

	return m_fps;
}

void FpsLimiter::setMaxFPS(float maxFPS)
{
	m_maxFPS = maxFPS;
}

void FpsLimiter::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = epochTime();
	float currentTicks;
	currentTicks = epochTime();

	m_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	//Average frame time
	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	//Calculate FPS
	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}
}

float FpsLimiter::epochTime()
{
	auto epochTime = std::chrono::high_resolution_clock::now();
	float msEpochTime = std::chrono::duration<float, std::milli>(epochTime.time_since_epoch()).count();

	return msEpochTime;
}