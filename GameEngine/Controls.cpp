#include "GameEngine.cpp"

//Template
/*
class Template : public Control {
	bool trigger(KeyboardIn mouse, KeyboardOut keys) {
		return keys.checkPress(mouse.getKeyListAt(Keyboard::Key), Keyboard::Key);
	}
	void event(GameEngine* g) {
		//do something
	}
};
*/

using namespace sf;
using namespace std;

class Right : public Control {
public:
	bool right = false;

	bool trigger(KeyboardIn mouse, KeyboardOut keys) {
		return keys.checkPressed(mouse.getKeyListAt(Keyboard::D), Keyboard::D);
	}
	void event(GameEngine* g) {
		GameObject* object = g->objects->getIndex(1)->object;
		*object->xPos = *object->xPos + 10;
		cout << *object->xPos << endl;
		object->node->animation->setAnimation(0);
	}
};
class Left : public Control {
public:
	bool left = false;
	bool trigger(KeyboardIn mouse, KeyboardOut keys) {
		return keys.checkPressed(mouse.getKeyListAt(Keyboard::A), Keyboard::A);
	}
	void event(GameEngine* g) {
		GameObject* object = g->objects->getIndex(1)->object;
		object->node->animation->setAnimation(1);
		unique_ptr<int> temp(new int(*object->xPos - 10));
		*object->xPos = *object->xPos - 10;
	}
};