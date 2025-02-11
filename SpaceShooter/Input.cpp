#include "Input.h"

Input::Input()
{}

void Input::update()
{

}

void Input::pressKey(unsigned int keyID)
{
	m_keyMap[keyID] = true;
}

void Input::releaseKey(unsigned int keyID)
{
	m_keyMap[keyID] = false;
}

bool Input::isKeyDown(unsigned int keyID)
{

}

bool Input::isKeyPressed(unsigned int keyID)
{ 
	
}

bool Input::wasKeyDown(unsigned int keyID)
{ 
	
}