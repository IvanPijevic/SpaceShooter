#include "Stats.h"


void Stats::draw(std::vector<CHAR_INFO>& buffer, Size windowSize)
{
	std::string stats = "Score: " + std::to_string(m_score) +
		"  Level: " + std::to_string(m_level) +
		"  Lives: " + std::to_string(m_lives);

	for (int i = 0; i < stats.size(); i++)
	{
		m_draw.drawPixel(static_cast<int>(i + 2), 2, stats[i], FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, windowSize, buffer);
	}
}