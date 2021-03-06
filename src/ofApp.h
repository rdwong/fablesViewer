#pragma once

#include "Globals.h"
#include "SketchPass.h"
#include "BSPass.h"
#include "PointPass.hpp"
#include "liquifyPass.h"

#ifdef TARGET_OSX
#define TEST_VID
#endif

class ofApp : public ofBaseApp{

    ofVec2f center;
    
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
		
    void ofExit();
    
    bool debug;
    
    ofFbo rawTexture;
    ofFbo buffer;
    
    ofVideoGrabber grab[2];
    vector<ofVideoDevice> devices;
    
#ifdef TEST_VID
    ofVideoPlayer testVid;
#endif
    
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
    
    void refreshCams();
    
    void saveSettings();
    void loadSettings();
    
    // Passes
    LiquifyPass* liquify;
    SketchPass* sketch;
    BSPass* bitshift;
    PointPass* points;
    Pass* scene[4];
    
    // Timing
    float cdRatio;
    int countdownTimer;
    int curScene;
    ofEvent<void> timerEndEvent;
    void endCurrentScene();
    void nextScene();
};


