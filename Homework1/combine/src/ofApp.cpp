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


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    cameraRotation.set(0);
    zoom = -500;
    zoomTarget = 200;
    
    billboards.getVertices().resize(NUM_BILLBOARDS);
    billboards.getColors().resize(NUM_BILLBOARDS);
    billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));
    
    // ------------------------- billboard particles
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
        billboards.getVertices()[i].set(ofRandom(-500, 500),
                                        ofRandom(-500, 500),
                                        ofRandom(-500, 500));
        
        billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(96, 160), 255, 255));
        billboardSizeTarget[i] = ofRandom(4, 64);
        
    }
    
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    
    // load the billboard shader
    // this is used to change the
    // size of the particle
    if(ofGetGLProgrammableRenderer()){
        billboardShader.load("shadersGL3/Billboard");
    }else{
        billboardShader.load("shadersGL2/Billboard");
    }
    
    // we need to disable ARB textures in order to use normalized texcoords
    ofDisableArbTex();
    texture.loadImage("dot.png");
    ofEnableAlphaBlending();
    
    //initialize the video grabber
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);
    
    //store the width and height for convenience
    int width = vidGrabber.getWidth();
    int height = vidGrabber.getHeight();
    
    //add one vertex to the mesh for each pixel
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
												// this replicates the pixel array within the camera bitmap...
            mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
        }
    }
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);				// 0
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex(x+(y+1)*width);			// 10
            
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex((x+1)+(y+1)*width);		// 11
            mainMesh.addIndex(x+(y+1)*width);			// 10
        }
    }
    
    //this is an annoying thing that is used to flip the camera
    cam.setScale(1,-1,1);
    
    
    //this determines how much we push the meshes out
    extrusionAmount = 300.0;
}

//--------------------------------------------------------------
void ofApp::update() {
    
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        // noise
        ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
        
        vec *= 10 * ofGetLastFrameTime();
        billboardVels[i] += vec;
        billboards.getVertices()[i] += billboardVels[i];
        billboardVels[i] *= 0.94f;
        billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
    }
    
    
    // move the camera around
    float mx = (float)mouseX/(float)ofGetWidth();
    float my = (float)mouseY/(float)ofGetHeight();
    ofVec3f des(mx * 360.0, my * 360.0, 0);
    cameraRotation += (des-cameraRotation) * 0.03;
    zoom += (zoomTarget - zoom) * 0.03;
    
    //grab a new frame
    vidGrabber.update();
    
    //update the mesh if we have a new frame
    if (vidGrabber.isFrameNew()){
        //this determines how far we extrude the mesh
        for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){
            
            ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
                                     vidGrabber.getPixels()[i*3+1]/255.f,			// g
                                     vidGrabber.getPixels()[i*3+2]/255.f);			// b
            
            //now we get the vertex aat this position
            //we extrude the mesh based on it's brightness
            ofVec3f tmpVec = mainMesh.getVertex(i);
            tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
            mainMesh.setVertex(i, tmpVec);
            
            mainMesh.setColor(i, sampleColor);
        }
    }
    
    //let's move the camera when you move the mouse
    float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);
    
    
    //move the camera around the mesh
    ofVec3f camDirection(0,0,1);
    ofVec3f centre(vidGrabber.getWidth()/2.f,vidGrabber.getHeight()/2.f, 255/2.f);
    ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, ofVec3f(1,0,0));
    ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
    
    cam.setPosition(camPosition);
    cam.lookAt(centre);

    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackgroundGradient(ofColor(255), ofColor(230, 240, 255));
    
    string info = ofToString(ofGetFrameRate(), 2)+"\n";
    info += "Particle Count: "+ofToString(NUM_BILLBOARDS);
    ofDrawBitmapStringHighlight(info, 30, 30);
    
    ofSetColor(255);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
    ofRotate(cameraRotation.x, 1, 0, 0);
    ofRotate(cameraRotation.y, 0, 1, 0);
    ofRotate(cameraRotation.y, 0, 0, 1);
    
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    texture.getTextureReference().bind();
    billboards.draw();
    texture.getTextureReference().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    
    ofPopMatrix();
    
    //we have to disable depth testing to draw the video frame
    ofDisableDepthTest();
    //	vidGrabber.draw(20,20);
    
    //but we want to enable it to show the mesh
    ofEnableDepthTest();
    cam.begin();
    
    //You can either draw the mesh or the wireframe
    // mainMesh.drawWireframe();
    mainMesh.drawFaces();
    cam.end();
    
    //draw framerate for fun
    ofSetColor(255);
    string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(msg, 10, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'f') ofToggleFullscreen();
    if(key == OF_KEY_UP) zoomTarget +=10;
    if(key == OF_KEY_DOWN) zoomTarget -=10;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
