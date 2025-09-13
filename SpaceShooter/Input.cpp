#include "Input.h"

void Input::update()
{
	for (auto it = m_keyMap.begin(); it != m_keyMap.end(); it++)
	{
		m_previousKeyMap[it->first] = it->second;
	}
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
	auto it = m_keyMap.find(keyID);
	if (it != m_keyMap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}

bool Input::isKeyPressed(unsigned int keyID)
{ 
	//Check if it is pressed this frame and was not pressed last frame (First click)
	if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false)
	{
		return true;
	}

	return false;
}

bool Input::wasKeyDown(unsigned int keyID)
{ 
	auto it = m_previousKeyMap.find(keyID);
	if (it != m_previousKeyMap.end())
	{
		return it->second;
	}
	else
	{
		return false;
	}
}