#include "Draw.h"

void Draw::drawPixel(short x, short y, wchar_t ch, WORD attributes, Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	if (x >= 0 && x < windowSize.width && y >= 0 && y < windowSize.height)
	{
		buffer[y * windowSize.width + x] = CHAR_INFO{ {ch}, attributes };
	}
}