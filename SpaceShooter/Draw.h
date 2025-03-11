#ifndef DRAW_H
#define DRAW_H

#include <Windows.h>
#include <vector>

#include "DataStructures.h"

class Draw
{
public:
	//Draw character, buffer = width * height
	void drawPixel(short x, short y, wchar_t ch, WORD attributes, Size windowSize, std::vector<CHAR_INFO>& buffer);

private:

};

#endif  //DRAW_H