#pragma once

#include "ofMain.h"

class Box{
public:
    
        void setup(float mX, float mY, float mZ);
        void update(float m);
        void draw(float r);
        
        ofVec3f pos;
        ofVec3f vel;
        
        ofVec2f pos2;
        ofVec2f vel2;
        
        ofColor color;
};

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
				
    void audioIn(float * input, int bufferSize, int nChannels);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;

    
    ofSoundStream soundStream;
    
    vector<Box> boxVector;
    int counter;
};
