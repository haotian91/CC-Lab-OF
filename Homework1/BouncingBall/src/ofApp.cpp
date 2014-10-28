#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    xPos = 0;
    xVel = 10;

}

//--------------------------------------------------------------
void ofApp::update(){
    if(xPos>=ofGetWidth()){
        xVel = -xVel;
    }
    if(xPos<0){
        xVel= -xVel;
    }
    xPos += xVel;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofCircle(xPos, ofGetHeight()/2, 20);
    
    

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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
