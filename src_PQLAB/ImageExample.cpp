#include "ImageExample.h"

//--------------------------------------------------------------
void ImageExample::setup(){
	ofSetFrameRate(60);
	// Connect
	MyClient.connect(3333);

	ofAddListener(ofEvents().touchDown, this, &ImageExample::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &ImageExample::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &ImageExample::touchUp);

	m_OpenGLRenderer = new ofGLRenderer();

	album.load("al.jpg",(WINDOW_WIDTH / 2),(WINDOW_HEIGHT / 2),100,100,0);
	album.setVisible(true);


	photos[0].load("test.jpg",(WINDOW_WIDTH / 2),(WINDOW_HEIGHT / 2) + 200,100,100,0);
	photos[1].load("test.jpg",(WINDOW_WIDTH / 2),(WINDOW_HEIGHT / 2) - 200,100,100,0);
	photos[2].load("test.jpg",(WINDOW_WIDTH / 2) - 200,(WINDOW_HEIGHT / 2),100,100,0);
	photos[3].load("test.jpg",(WINDOW_WIDTH / 2) + 200,(WINDOW_HEIGHT / 2),100,100,0);

	time = -1;
	isDoubleTap = false;
}

//--------------------------------------------------------------
void ImageExample::update(){

}

//--------------------------------------------------------------
void ImageExample::draw(){

	m_OpenGLRenderer.pushMatrix();
	m_OpenGLRenderer.translate((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));
	m_OpenGLRenderer.rotateZ(0);

	m_OpenGLRenderer.draw(album, -album.getWidth() / 2, -album.getHeight() / 2, 0.0,
		100, 100,
		0.0, 0.0,
		100, 100);

	m_OpenGLRenderer.popMatrix();

	for(int i=0;i<4;i++){
		if(photos[i].isVisible()){
			m_OpenGLRenderer.pushMatrix();
			m_OpenGLRenderer.translate(photos[i].getPosX(), photos[i].getPosY());
			m_OpenGLRenderer.rotateZ(photos[i].getAngle());

			m_OpenGLRenderer.draw(photos[i], -photos[i].getWidth() / 2, -photos[i].getHeight() / 2, 0.0,
				photos[i].getWidth(), photos[i].getHeight(),
				0.0, 0.0,
				photos[i].getWidth(), photos[i].getHeight());

			m_OpenGLRenderer.popMatrix();
		}
	}


}

//--------------------------------------------------------------
void ImageExample::keyPressed(int key){

}

//--------------------------------------------------------------
void ImageExample::keyReleased(int key){

}

//--------------------------------------------------------------
void ImageExample::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ImageExample::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ImageExample::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ImageExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ImageExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ImageExample::dragEvent(ofDragInfo dragInfo){ 

}

void ImageExample::touchDown( ofTouchEventArgs & touch )
{

	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;


	// move image
	if ( MyClient.client->getTuioCursors().size() == 1 )
	{
		photoNum = checkPhoto(touch, photos);

		unsigned long long curTime = ofGetElapsedTimeMillis();

		if(time != -1 && curTime - time < 300){
			isDoubleTap = true;
		}
		else
			time = -1;

		// 더블탭이면 안보이기
		if(isDoubleTap){
			for(int i=0;i<4;i++)
				photos[i].setVisible(false);

			isDoubleTap = false;
			time = -1;
		}
		else {
			// 비어있으면
			for(int i=0;i<4;i++)
				photos[i].setVisible(true);

			if(time == -1)
				time = ofGetElapsedTimeMillis();

		}
	}

	if ( MyClient.client->getTuioCursors().size() == 4 )
	{


		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
			case 3:
				cursor4 = iter;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor4 == nullptr )
		{
			return;
		}
		prevAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
	}


}

void ImageExample::touchMoved( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;
	TUIO::TuioCursor* cursor4 = nullptr;



	if(photoNum != -1){
		if ( MyClient.client->getTuioCursors().size() == 1 )
		{
			for ( auto *iter : MyClient.client->getTuioCursors() )
			{
				if (iter->getCursorID() == 0)
				{
					cursor1 = iter;
				}
			}

			if (cursor1 == nullptr)
			{
				return;
			}

			int movedPositionX = cursor1->getX() * WINDOW_WIDTH * 2;
			int movedPositionY = cursor1->getY() * WINDOW_HEIGHT * 2;

			// if imaged moved too far, return;
			if ( (photos[photoNum].getPosX() - movedPositionX) > 10.0 || photos[photoNum].getPosY() - movedPositionY > 10.0 )
			{
				return;
			}

			photos[photoNum].setPosX(cursor1->getX() * WINDOW_WIDTH);
			photos[photoNum].setPosY(cursor1->getY() * WINDOW_HEIGHT);
		}

		if ( MyClient.client->getTuioCursors().size() == 2 )
		{
			for ( auto *iter : MyClient.client->getTuioCursors() )
			{
				switch ( iter->getCursorID() )
				{
				case 0:
					cursor1 = iter;
					break;
				case 1:
					cursor2 = iter;
					break;
				default:
					break;
				}
			}

			// 방어코드
			if (cursor1 == nullptr || cursor2 == nullptr)
			{
				return;
			}

			photos[photoNum].setWidth(abs( cursor1->getX() - cursor2->getX() ) * WINDOW_WIDTH);
			photos[photoNum].setHeight(abs( cursor1->getY() - cursor2->getY() ) * WINDOW_HEIGHT);
		}

		// rotate
		if ( MyClient.client->getTuioCursors().size() == 3 )
		{
			for ( auto *iter : MyClient.client->getTuioCursors() )
			{
				switch ( iter->getCursorID() )
				{
				case 0:
					cursor1 = iter;
					break;
				case 1:
					cursor2 = iter;
					break;
				default:
					break;
				}
			}

			// 방어코드
			if (cursor1 == nullptr || cursor2 == nullptr)
			{
				return;
			}
			// 포인트 1과 2의 기울기를 기준으로 회전시킨다.
			double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
			photos[photoNum].setAngle(180.0 * atan(tempAngle) / PI);
		}
	}
	// squueze & splay
	if ( MyClient.client->getTuioCursors().size() == 4 )
	{

		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			case 2:
				cursor3 = iter;
			case 3:
				cursor4 = iter;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor4 == nullptr )
		{
			return;
		}

		// 포인트 1과 2의 기울기를 기준으로 회전시킨다.
		double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
		
		// bigger
		if(tempAngle > prevAngle){
			for(int i=0;i<4;i++){
				if(photos[i].getPosX() >= WINDOW_WIDTH / 2 + 100)
					photos[i].setPosX(photos[i].getPosX() + 2);
				else if (photos[i].getPosX() < WINDOW_WIDTH / 2 - 100)
					photos[i].setPosX(photos[i].getPosX() - 2);

				if(photos[i].getPosY() >= WINDOW_HEIGHT / 2 + 100)
					photos[i].setPosY(photos[i].getPosY() + 2);
				else if(photos[i].getPosY() < WINDOW_HEIGHT / 2 - 100)
					photos[i].setPosY(photos[i].getPosY() - 2);
			}
		}
		// smaller
		else{
			for(int i=0;i<4;i++){
				if(photos[i].getPosX() >= WINDOW_WIDTH / 2 + 100)
					photos[i].setPosX(photos[i].getPosX() - 2);
				else if (photos[i].getPosX() < WINDOW_WIDTH / 2 - 100)
					photos[i].setPosX(photos[i].getPosX() + 2);

				if(photos[i].getPosY() >= WINDOW_HEIGHT / 2 + 100)
					photos[i].setPosY(photos[i].getPosY() - 2);
				else if(photos[i].getPosY() < WINDOW_HEIGHT / 2 - 100)
					photos[i].setPosY(photos[i].getPosY() + 2);
			}
		}



	}
}

void ImageExample::touchUp( ofTouchEventArgs & touch )
{

}

int ImageExample::checkPhoto(ofTouchEventArgs& touch, Photo photos[])
{
	for (int i = 0 ; i<4 ; ++i)
	{
		if (photos[i].getPosX()<=touch.x*WINDOW_WIDTH && photos[i].getPosX()+photos[i].getWidth() >= touch.x*WINDOW_WIDTH
			&& photos[i].getPosY()<=touch.y*WINDOW_HEIGHT && photos[i].getPosY()+photos[i].getHeight() >= touch.y*WINDOW_HEIGHT)
		{
			return i;
			break;
		}
	}

	return -1;
}