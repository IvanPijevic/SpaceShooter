#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>

class Input
{
public:
	Input();

	void update();
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);

	bool isKeyDown(unsigned int keyID);  //True ako je tipka pritisnuta
	bool isKeyPressed(unsigned int keyID); //True ako je samo stisnuta(pucaj jednom bez obzira koliko dugo je stisnuta tipka)

private:
	bool wasKeyDown(unsigned int keyID);

private:
	std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;  //zadnji frame
};

#endif  //INPUT_H