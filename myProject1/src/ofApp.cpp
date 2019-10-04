#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	counter = 0;

	beat1.load("sounds/beat1.wav");
	beat2.load("sounds/beat2.wav");
	beat3.load("sounds/beat3.wav");
	beat4.load("sounds/beat4.wav");

	beats.load("sounds/slot-machine.wav");
	beats.setVolume(0.75f);
	beats.setMultiPlay(false);

	beats.setLoop(true);

}

//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(157, 41, 50);

	// update the sound playing system:
	ofSoundUpdate();

	// (1) we increase px and py by adding vx and vy
	px += vx;
	py += vy;

	// (2) check for collision, and trigger sounds:
	// horizontal collisions:
	if (px < 0) {
		px = 0;
		vx *= -1;
		beat1.play();
	}
	else if (px > ofGetWidth()) {
		px = ofGetWidth();
		vx *= -1;
		beat2.play();
	}
	// vertical collisions:
	if (py < 0) {
		py = 0;
		vy *= -1;
		beat3.play();
	}
	else if (py > ofGetHeight()) {
		py = ofGetHeight();
		vy *= -1;
		beat4.play();
	}

	// (3) slow down velocity:
	vx *= 0.97f;
	vy *= 0.97f;

	// update event slowly increments the counter variable
	counter = counter + 0.033f;

	for (auto &vert : line.getVertices()) {
		vert.x += ofRandom(-2, 2);
		vert.y += ofRandom(-2, 2);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// finally draw the playing circle:

	ofEnableAlphaBlending();
	ofSetColor(254, 199, 116, 40);
	ofDrawCircle(px, py, 40);
	ofDisableAlphaBlending();

	ofSetColor(254, 199, 116, 30);
	float radius = 15 + 5 * sin(counter);
	//	ofFill();		// draw "filled shapes"
	ofDrawCircle(px, py, radius);

	ofSetColor(245, 247, 244, 30);
	line.draw();

	//---------------------------------- beats:
	if (beats.isPlaying()) ofSetHexColor(0xFF0000);
	else ofSetHexColor(0x000000);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	beats.setSpeed(0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
	beats.setPan(0.5f + ((float)(ofGetWidth() - x) / (float)ofGetWidth())*1.0f);

	// add into vx and vy a small amount of the change in mouse:
	vx += (x - prevx) / 20.0f;
	vy += (y - prevy) / 20.0f;
	// store the previous mouse position:
	prevx = x;
	prevy = y;


	ofPoint pt;
	pt.set(x, y);
	line.addVertex(pt);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	prevx = x;
	prevy = y;

	line.clear();

	float widthStep = ofGetWidth() / 3.0f;
	if (button == 0) {
		beats.play();
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
