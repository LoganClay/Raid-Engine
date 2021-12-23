#pragma once
#include <iostream>

using namespace std;

class Hitbox
{
public:
	shared_ptr<int> x, y;
	shared_ptr<int> w, h;

	Hitbox(shared_ptr<int> x, shared_ptr<int> y, shared_ptr<int> h, shared_ptr<int> w);

	bool detect( Hitbox box );
	
	void setX(int* x);
	void setY(int* y);
	void setW(int* h);
	void setH(int* w);
};

