#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <vector>

#include "DataStructures.h"

class Window
{
public:
	//Window(Size screenSize);
	Window(short width, short height);
	~Window();

	void Clear();
	void Draw();
	void SetPixel(short x, short y, wchar_t ch, WORD attributes = FOREGROUND_INTENSITY);

private:
	HANDLE m_frontBuffer; 
	HANDLE m_backBuffer;

	Position m_windowPosition;
	Size m_windowSize;
	std::vector<CHAR_INFO> m_buffer;

	short m_width;
	short m_height;
};

#endif  //WINDOW_H