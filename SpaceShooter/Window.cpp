#include "Window.h"

Window::Window(Size screenSize) : 
	m_screenSize(screenSize),
	m_buffer(screenSize.x * screenSize.y)
{
	m_frontBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	m_backBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
												NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(m_frontBuffer, m_screenSize);
}

Window::~Window()
{ }

