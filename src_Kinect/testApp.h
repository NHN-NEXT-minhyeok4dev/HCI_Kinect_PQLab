#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "rect.h"
#include <array>

#define MAX_DEVICES 2
#define MAX_NUMBER_OF_HAND 4

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

private:
    void handEvent(ofxOpenNIHandEvent & event);
    
	ofxOpenNI openNIDevice;
	mRect rect[2];

};

#endif
