/**
 *
 * OFDevCon Example Code Sprint
 *
 * This example shows building a mesh, texturing it with a webcam, and extruding the vertices based on the pixel brightness
 * Moving the mouse also rotates the mesh to see it at different angles
 *
 * Created by Tim Gfrerer and James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */


#pragma once
#include "ofMain.h"
#include "ofVbo.h"

#define NUM_BILLBOARDS 5000

class ofApp : public ofBaseApp {
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
    
    ofVec3f cameraRotation;
    float zoom, zoomTarget;
    
    // billboard particles
    float billboardSizeTarget[NUM_BILLBOARDS];
    
    ofShader billboardShader;
    ofImage texture;
    
    ofVboMesh billboards;
    ofVec3f billboardVels[NUM_BILLBOARDS];
    
    
    ofCamera cam; // add mouse controls for camera movement
    float extrusionAmount;
    ofVboMesh mainMesh;
    ofVideoGrabber vidGrabber;

};









