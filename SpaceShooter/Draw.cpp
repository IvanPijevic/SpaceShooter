#include "Draw.h"

void Draw::drawPixel(short x, short y, wchar_t ch, WORD attributes, Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	if (x >= 0 && x < windowSize.x && y >= 0 && y < windowSize.y)
	{
		buffer[y * windowSize.x + x] = CHAR_INFO{ {ch}, attributes };
	}
}