//
//  Globals.h
//  fablesViewer
//
//  Created by Richard Wong on 11/03/2016.
//
//

#ifndef __fablesViewer__Globals__
#define __fablesViewer__Globals__

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#define SCREEN_W    800
#define SCREEN_H    480

#define CAM_RES_X   640
#define CAM_RES_Y   480

#define GUI Globals::gui

#define FRAMES_PER_SCENE    (60*5)

namespace Globals
{
    extern ofxPanel* gui;
};

static void canvas(float width, float height)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);     glVertex2f(0, 0);
    glTexCoord2f(width, 0);     glVertex2f(width, 0);
    glTexCoord2f(width, height);    glVertex2f(width, height);
    glTexCoord2f(0, height);    glVertex2f(0, height);
    glEnd();
}

#define WARP_RES_X  28
#define WARP_RES_Y  18

class RGBFbo : public ofFbo
{
public:
    RGBFbo() { allocate(SCREEN_W, SCREEN_H, GL_RGB); }
};
class RGBAFbo : public ofFbo
{
public:
    RGBAFbo() { allocate(SCREEN_W, SCREEN_H, GL_RGBA); }
};

static void lensCanvas(float width, float height)
{
    glBegin(GL_TRIANGLE_STRIP);
    
    float portW = width*0.5;
    float xInterval = 0.5*width/WARP_RES_X;
    float yInterval = 0.5*height/WARP_RES_Y;
    
    // left half
    for (int i = 0; i < WARP_RES_X; i++) {
        float xratio = float(i)/WARP_RES_X;
        
        float normalx = xratio*portW;
        float warpx = portW*0.5*(1 + sin(xratio*PI - HALF_PI));
        
        glTexCoord2f(normalx, 0);
        glVertex2f(warpx, 0);
        glTexCoord2f(normalx, height);
        glVertex2f(warpx, height);
    }
    
    // right half
    for (int i = 0; i < WARP_RES_X; i++) {
        float xratio = float(i)/WARP_RES_X;
        
        float normalx = portW + xratio*portW;
        float warpx = portW + portW*0.5*(1 + sin(xratio*PI - HALF_PI));
        
        glTexCoord2f(normalx, 0);
        glVertex2f(warpx, 0);
        glTexCoord2f(normalx, height);
        glVertex2f(warpx, height);
    }
    
    glEnd();
}

#endif /* defined(__fablesViewer__Globals__) */
