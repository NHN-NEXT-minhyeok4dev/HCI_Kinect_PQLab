#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {

	openNIDevice.setup();
	openNIDevice.addImageGenerator();
	openNIDevice.addDepthGenerator();
	openNIDevice.setRegister(true);
	openNIDevice.setMirror(true);

	// setup the hand generator
	openNIDevice.addHandsGenerator();

	openNIDevice.addAllHandFocusGestures();

	openNIDevice.setMaxNumHands(MAX_NUMBER_OF_HAND);

	openNIDevice.start();

	// hand event를 담당하는 리스너 등록
	ofAddListener(openNIDevice.handEvent, this, &testApp::handEvent);

	rect[0].setup(200, 50);
	rect[1].setup(400, 300);

	srand(time(NULL));
}

//--------------------------------------------------------------
void testApp::update(){
	openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);

	openNIDevice.drawImage(0,0,640,480);

	ofPushMatrix();
	// get number of current hands
	int numHands = openNIDevice.getNumTrackedHands();

	// iterate through users
	for (int i = 0; i < numHands; i++){
		ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);

		ofPoint& handPosition = hand.getPosition();

		ofSetColor(255,0,0);
		ofRect(handPosition.x, handPosition.y, 10, 10);
		for(int i=0;i<2;i++){
			if(rect[i].isCollision(handPosition)){

				rect[i].setColor(rand()%256,rand()%256,rand()%256);
			}
		}
	}
	ofPopMatrix();

	for(int i=0;i<2;i++)
		rect[i].draw();
	


}

//--------------------------------------------------------------
void testApp::handEvent(ofxOpenNIHandEvent & event){
}

//--------------------------------------------------------------
void testApp::exit(){
	openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}