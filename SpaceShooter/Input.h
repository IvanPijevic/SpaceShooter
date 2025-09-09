#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>

enum class Keys
{
	W = 0x57, A = 0x41, S = 0x53, D = 0x44, ESC = 0x1B
};

class Input
{
public:
	Input();

	void update();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	bool isKeyDown(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);

private:
	bool wasKeyDown(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;
};

#endif  //INPUT_H