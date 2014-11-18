#include "ofApp.h"

//--------------------------------------------------------------
void Box::setup(float mX, float mY,float mZ){
    pos.set(mX, mY, -1000);
    pos2.set(ofRandomWidth(), ofRandomHeight());
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Box::update(float m){
    
    vel.x = ofRandom(-m,m);
    vel.y = ofRandom(-m,m);
    vel.z = ofRandom(m,m*10);
    
    vel2.x = ofRandom(-m*5,m*5);
    vel2.y = ofRandom(-m*4,m*4);
    pos += vel;
    pos2 += vel2;
}


void Box::draw(float r){
    ofNoFill();
    ofSetColor(color);
    ofCircle(pos2.x, pos2.y, r/5);
    ofDrawIcoSphere(pos.x, pos.y, pos.z, r);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    ofNoFill();
    
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    soundStream.listDevices();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
//ball______________________
    counter ++;
    
    if (counter >= 5) {
        Box sgtPepper;
        sgtPepper.setup(ofGetWindowWidth()/2, ofGetWindowHeight()/2,scaledVol*0.01);
        boxVector.push_back(sgtPepper);
        counter=0;
    };
    
    for (int i=0; i<boxVector.size();i++){
        boxVector[i].update(scaledVol*10);
    };
    
    while (boxVector.size()>100) {
        boxVector.erase(boxVector.begin());
    };

//ball_______________________
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(245, 58, 135);
    ofFill();
    for (int i =0;  i<boxVector.size(); i++) {
        boxVector[i].draw(scaledVol*100);
    };
    
    ofSetColor(255);
   }

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
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

