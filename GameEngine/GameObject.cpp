#include "GameObject.h"

using namespace sf;

//Template

/*
Game Object template

class template : public GameObject {

public:
	template(Render* render) {
		spriteW = 1920;
		spriteH = 1080;
		unitsW = 2;
		unitsH = 2;

		texture.loadFromFile("Textures\\template.png", IntRect(0, 0, 1920, 1080));
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		createStillAnimation(animation); // fillAnimation(animation, 0, 0, 0, 20);

		node->animation->addAnimation(0, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
	}
};*/
class Background : public GameObject {

public:
	Background(Render* render) {
		spriteW =  make_shared<int>(1920);
		spriteH = make_shared<int>(1080);
		xPos = make_shared<int>(0);
		yPos = make_shared<int>(0);

		unitsW = 1;
		unitsH = 1;

		texture.loadFromFile("Textures\\Test_Background.png", IntRect(0, 0, 1920, 1080));
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		createStillAnimation(animation, 0, 0); // fillAnimation(animation, 0, 0, 0, 20);

		node->animation->addAnimation(0, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
	}
};

class Man : public GameObject {

public:
	Man(Render* render) {
		spriteW = make_shared<int>(500);
		spriteH = make_shared<int>(500);
		xPos = make_shared<int>(200);
		yPos = make_shared<int>(150);
		unitsW = 7;
		unitsH = 2;

		texture.loadFromFile("Textures\\Test_Man.png");
		Sprite sprite = Sprite(texture);

		node = render->addToRender(sprite, xPos, yPos, spriteW, spriteH);
		nodeNum = render->getSize();

		//Animations
		int animation[60][2];

		/*stand still left
		createStillAnimation(animation, 0, 0);
		node->animation->addAnimation(0, animation);

		//stand still right
		createStillAnimation(animation, 0, 1);
		node->animation->addAnimation(1, animation);
		*/

		//run right
		fillAnimation(animation, 0, 1 , 0, 8);
		fillAnimation(animation, 1, 1,  8, 8);
		fillAnimation(animation, 2, 1, 16, 8);
		fillAnimation(animation, 3, 1, 24, 8);
		fillAnimation(animation, 4, 1, 32, 8);
		fillAnimation(animation, 5, 1, 40, 10);
		fillAnimation(animation, 6, 1, 50, 10);

		node->animation->addAnimation(0, animation);

		fillAnimation(animation, 0, 0, 0, 8);
		fillAnimation(animation, 1, 0, 8, 8);
		fillAnimation(animation, 2, 0, 16, 8);
		fillAnimation(animation, 3, 0, 24, 8);
		fillAnimation(animation, 4, 0, 32, 8);
		fillAnimation(animation, 5, 0, 40, 10);
		fillAnimation(animation, 6, 0, 50, 10);

		node->animation->addAnimation(1, animation);

		this->hitbox = new Hitbox(this->xPos, this->yPos, this->spriteW, this->spriteH);
	}
};