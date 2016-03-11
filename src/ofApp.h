#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

#define SCREEN_W    800
#define SCREEN_H    450

#define CAM_RES_X   600
#define CAM_RES_Y   450

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    bool debug;
    
    ofFbo rawTexture;
    ofFbo buffer;
    
    ofShader outlineShader;
    ofShader shadingShader;
    ofFbo shadeFbo;
    ofFbo outlineFbo;
    
    ofxCvGrayscaleImage gray;
    ofVideoGrabber grab[2];
    vector<ofVideoDevice> devices;
    
    int portW;
    int portH;
    int offX, offY;
    
    // Admin
    ofxPanel guiAdmin;
    ofxButton saveBtn;
    ofxButton loadBtn;
    
    // Camera Stuff
    ofxPanel guiCamera;
    ofxIntSlider toggleCam[2];
    ofxButton refreshCamBtn;
    ofxToggle swapCams;
    ofxFloatSlider scaleCams;
    
    // Shader Stuff
    ofxPanel guiShaderSketch;
    ofxFloatSlider shadeThreshold;
    ofxFloatSlider outlineThreshold;
    
    ofxPanel gui;
    
    void refreshCams();
    void toggleCamAID();
    void toggleCamBID();
    
    void saveSettings();
    void loadSettings();
    
    void canvas(float width, float height)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);     glVertex2f(0, 0);
        glTexCoord2f(width, 0);     glVertex2f(width, 0);
        glTexCoord2f(width, height);    glVertex2f(width, height);
        glTexCoord2f(0, height);    glVertex2f(0, height);
        glEnd();
    }
    
};
