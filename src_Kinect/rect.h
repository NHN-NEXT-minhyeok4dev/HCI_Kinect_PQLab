#pragma once

#include "ofMain.h"

class mRect{
public:

	float getPosX(){return posX;}
	float getPosY(){return posY;}

	void setup(float x, float y){ posX = x; posY = y; dirX = 5; dirY = 5; color[0]=0; color[1]=0; color[2] = 0;}
	void draw();
	void setColor(int r, int g, int b) {color[0] = r; color[1] = g; color[2] = b;}
	bool isCollision(ofPoint & handPosition);

private:
	float posX;
	float posY;
	float dirX;
	float dirY;

	int color[3];
	

};