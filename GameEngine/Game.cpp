#include "Controls.cpp"
#include <thread>

using namespace std;

int main() {
	//Create Engine object
	GameEngine* engine = new GameEngine();
	
	Controls* controls = engine->controls;
	ObjectList* objects = engine->objects;
	Render* render = engine->render;

	//load first menu


	//start the game
	engine->start();
}
