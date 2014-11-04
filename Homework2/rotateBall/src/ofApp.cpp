#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    ofSetCircleResolution(50);
    
    one.setup();
    
    for(int i=0; i<NUM; i++){
        rotate[i].setup();}
    

}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0; i<NUM; i++){
        rotate[i].move();}
    }

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0; i<NUM; i++){
        rotate[i].display(i);}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    for(int i=0; i<NUM; i++){
        rotate[i].reset(mouseX, mouseY);}
    


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int i=0; i<NUM; i++){
        rotate[i].press(mouseX, mouseY);}
    
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
