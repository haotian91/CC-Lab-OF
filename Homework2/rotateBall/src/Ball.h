//
//  Ball.h
//  rotateBall
//
//  Created by 李昊天 on 11/4/14.
//
//

#pragma once

#include "ofMain.h"

class Ball{
    
public:
    
    //constructor
    Ball();
    
    //variables
    float posX, posY,disX,disY;
    
    float size,time;
    
    float velX, velY;
    
    float r, g, b;
    int X,Y;
    
    //methods
    void setup();
    void display(int i);
    void move();
    void reset(float newPosX, float newPosY);
    void press(float newPosX2, float newPosY2);
    
};