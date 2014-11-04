//
//  Ball.cpp
//  rotateBall
//
//  Created by 李昊天 on 11/4/14.
//
//

#include "Ball.h"

Ball::Ball(){
    posX = ofGetWindowWidth()/2;
    posY = ofGetWindowHeight()/2;
}

void Ball::setup(){
    size = 50;
    time = 0.00;
    r= 10;
    g= 20;
    b= 30;
    X=ofRandom(-2,2);
    Y=ofRandom(-2, 2);
}

void Ball::display(int i){

    ofSetColor(r, g, b);
    
    ofCircle(posX+disX/100*i*X, posY+disY/100*i*Y,size/5);
}

void Ball::move(){
    time +=0.02;
    
    velX = sin(time);
    velY = cos(time);
    
    disX = ofMap(velX, -1, 1, -300, 300);
    disY = ofMap(velY, -1, 1, -300, 300);
}

void Ball::reset(float newPosX, float newPosY){
    posX = newPosX;
    posY = newPosY;
}

void Ball::press(float newPosX2, float newPosY2){
    size +=10;
    r+=10;
    g+=10;
    b+=10;
    if(r>255){r= ofRandom(255);};
    if(g>255){g= ofRandom(255);};
    if(b>255){b= ofRandom(255);};
    
    
}



