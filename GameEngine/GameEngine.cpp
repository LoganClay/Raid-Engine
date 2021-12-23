#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <SFML/OpenGL.hpp>
#include "KeyboardIn.h"
#include "KeyboardOut.h"
#include "Render.h"
#include "Controls.h"
#include "GameObject.cpp"

using namespace std;
using namespace sf;
class GameEngine{
public:
	
	KeyboardIn keyboardIn;
	KeyboardOut keyboardOut;
	bool showFPS = false;
	bool pause = false;

	Render* render = new Render();
	Controls* controls =  new Controls();
	ObjectList* objects = new ObjectList();

	void start() {
		RenderWindow window;
		int width = 1920, height = 1080;

		bool menuBool=false;
		bool aniChange = false;

		window.create(VideoMode(width, height), "SimmerDownDaddy", Style::Titlebar | Style::Close);
		window.setVerticalSyncEnabled(true);
		window.setActive(true);

		Music titleMusic;
		if (!titleMusic.openFromFile("Music\\MenuTheme.wav")) {
			cout << "Nopey" << endl;
		}

		titleMusic.play();
		titleMusic.setVolume(2.5f);

		float hScale = (float)width / 1920, vScale = (float)height / 1080;


		Font arial;
		arial.loadFromFile("Fonts\\arial.ttf");

		int FPS = 60;
		Text fps;
		fps.setFont(arial);
		fps.setCharacterSize(24);
		fps.setFillColor(sf::Color::Yellow);
		fps.setString("FPS: " + to_string(FPS));

		sf::Clock clock;
		float timer = 0;
		int fpsCounter = 0;

		int spriteInt=0;
		bool boolKitchen = true;

		while (window.isOpen()) {
			fpsCounter++;
			sf::Time elapsed = clock.restart();
			//std::cout << elapsed.asSeconds() << " time elapsed since last check" << std::endl;
			timer += elapsed.asSeconds();
			if (timer >= 1) {
				//cout << timer << " time elapsed since last check" << endl;
				FPS = fpsCounter;
				fpsCounter = 0;
				timer = 0;		
			}
		


			Event event;
			keyboardOut.updateLastKey(keyboardIn.keyList);
			keyboardOut.updateLastButton(keyboardIn.buttonList);
			keyboardIn.mouseWheel = 0;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case Event::Closed:
					window.close();
					break;
					//Input Handling
				case Event::KeyPressed:
				case Event::KeyReleased:
				case Event::MouseButtonPressed:
				case Event::MouseButtonReleased:
				case Event::MouseWheelScrolled:
					keyboardIn.checkInput(event);
					break;
				case Event::MouseMoved:
					keyboardIn.setMouse(new int(event.mouseMove.x), new int(event.mouseMove.y));
					//std::cout << "Mouse X: " << keyboardIn.mouseXPos << " Mouse Y: " << keyboardIn.mouseYPos << std::endl;
					break;
				case sf::Event::Resized:
					glViewport(0, 0, event.size.width, event.size.height);
					break;
				default:
					break;
				}
			}

			//Doing Controls
			for (int i = 0; i < controls->controlsSize; i++) {
				Control *temp = controls->getIndex(i)->control;
				if (temp->trigger(keyboardIn, keyboardOut)) temp->event(this);
			}
			//rendering 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			window.clear();
			for (int i = 0; i < render->getSize(); i++) {
				window.draw(render->getIndex(i)->sprite);
					if (!pause) render->getIndex(i)->iterate();
			}
			fps.setString("FPS: " + std::to_string(FPS));
			if (showFPS)window.draw(fps);

			window.display();
		}
	}
};