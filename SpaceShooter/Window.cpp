#include "Window.h"

Window::Window(short width, short height) : 
	m_windowSize(width, height),
	m_buffer(width * height)
{
	m_frontBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	m_backBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 
												NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//Window size == buffer size
	SMALL_RECT windowSize = { 0, 0, m_windowSize.width - 1, m_windowSize.height - 1 };
	SetConsoleWindowInfo(m_frontBuffer, TRUE, &windowSize);
	SetConsoleWindowInfo(m_backBuffer, TRUE, &windowSize);

	//Postavljanje velicine oba window buffera
	SetConsoleScreenBufferSize(m_frontBuffer, m_windowSize);
	SetConsoleScreenBufferSize(m_backBuffer, m_windowSize);

	//Sakri mis
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	SetConsoleCursorInfo(m_frontBuffer, &cursorInfo);
	SetConsoleCursorInfo(m_backBuffer, &cursorInfo);

	SetConsoleActiveScreenBuffer(m_frontBuffer);

}

Window::~Window()
{
	SetConsoleActiveScreenBuffer(m_frontBuffer);
	CloseHandle(m_backBuffer);
}

void Window::Clear()
{
	std::fill(m_buffer.begin(), m_buffer.end(), CHAR_INFO{ {L' '}, FOREGROUND_INTENSITY });
}

//void Window::SetPixel(short x, short y, wchar_t ch, WORD attributes)
//{
//	if (x >= 0 && x < m_windowSize.x && y >= 0 && y < m_windowSize.y) 
//	{
//		m_buffer[y * m_windowSize.x + x] = CHAR_INFO{ {ch}, attributes };
//	}
//}

void Window::Draw()
{

	//Write entire buffer at once
	SMALL_RECT writeRegion = { 0, 0, m_windowSize.width - 1, m_windowSize.height - 1 };
	WriteConsoleOutputA(m_backBuffer, m_buffer.data(), m_windowSize, { 0, 0 }, &writeRegion);

	// Swap buffers
	SetConsoleActiveScreenBuffer(m_backBuffer);
	std::swap(m_frontBuffer, m_backBuffer);
}