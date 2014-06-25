#pragma once

#include "ofMain.h"

class Photo : public ofImage{
public:
	Photo(void);
	~Photo(void);

	float getPosX(){return posX;}
	float getPosY(){return posY;}

	float getWidth(){return width;}
	float getHeight(){return height;}

	float getAngle(){return angle;}
	bool isVisible(){return visible;}


	void setPosX(float data){posX = data;}
	void setPosY(float data){posY = data;}

	void setWidth(float data){width = data;}
	void setHeight(float data){height = data;}

	void setAngle(float data){angle = data;}

	void setVisible(bool data){visible = data;}

	void load(char* filename, float x, float y, float wid, float hei, float ang){
		loadImage(filename);
		posX = x;
		posY = y;
		width = wid;
		height = hei;
		angle = ang;
	}

private:
	float posX;
	float posY;
	float width;
	float height;
	float angle;

	bool visible;


};