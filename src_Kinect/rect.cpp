#include "rect.h"



void mRect::draw(){
	
	if(posY >= 480)
		dirY = -5;
	else if(posY <= 0)
		dirY = 5;

	if(posX >= 640)
		dirX = -5;
	else if(posX <= 0)
		dirX = 5;

	posX += dirX;
	posY += dirY;
	ofSetColor(color[0], color[1], color[2]);
	ofRect(posX, posY, 30, 30);
}

bool mRect::isCollision(ofPoint & handPosition){
	if(handPosition.x >= posX-15 && handPosition.x <= posX+15		
		&& handPosition.y >= posY-15 && handPosition.y <= posY+15)
		return true;

	return false;
}