#pragma once

#include "ofMain.h"
#include "ofxTuioClient.h"
// for openGL
#include "ofGLRenderer.h"
#include "photo.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

class ImageExample : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	// added to Example
		ofxTuioClient MyClient;

		void touchDown(ofTouchEventArgs & touch);
		void touchMoved(ofTouchEventArgs & touch);
		void touchUp(ofTouchEventArgs & touch);

		int checkPhoto(ofTouchEventArgs& touch, Photo photos[]);


private:
	ofGLRenderer m_OpenGLRenderer;

	Photo album;
	Photo photos[4];
	
	unsigned long long time;
	bool isDoubleTap;
	int photoNum;
	double prevAngle;
};
