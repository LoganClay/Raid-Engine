#include <SFML/Window/Event.hpp>
#include "KeyboardIn.h"
#include <iostream>

void KeyboardIn::checkInput(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed) this->keyList[e.key.code] = true;
	else if (e.type == sf::Event::KeyReleased) this->keyList[e.key.code] = false;

	if (e.type == sf::Event::MouseButtonPressed) this->buttonList[e.mouseButton.button] = true;
	else if (e.type == sf::Event::MouseButtonReleased) this->buttonList[e.mouseButton.button] = false;

	if (e.type == sf::Event::MouseWheelScrolled) mouseWheel = e.mouseWheelScroll.delta;

}

bool KeyboardIn::getKeyListAt(int i) { return this->keyList[i]; }
bool KeyboardIn::getButtonListAt(int i) { return this->buttonList[i]; }
void KeyboardIn::setMouse(int* x, int* y) {
	unique_ptr<int> tempX(x);
	unique_ptr<int> tempY(y);
	mouseXPos = move(tempX);
	mouseYPos = move(tempY);
}

KeyboardIn::KeyboardIn() {
	for (int i = 0; i < sizeof(this->keyList); i++) this->keyList[i] = false;
	for (int i = 0; i < sizeof(this->buttonList); i++) this->buttonList[i] = false;
	mouseWheel = 0;
	mouseXPos = make_shared<int>(0);
	mouseYPos = make_shared<int>(0);
	mouse = new Hitbox(mouseXPos,mouseYPos, make_shared<int>(1), make_shared<int>(1));
}
