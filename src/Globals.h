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
#define SCREEN_H    450

#define CAM_RES_X   600
#define CAM_RES_Y   450

#define GUI Globals::gui

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

#endif /* defined(__fablesViewer__Globals__) */
