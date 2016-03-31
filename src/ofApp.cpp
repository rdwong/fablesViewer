#include "ofApp.h"

void ofApp::ofExit()
{
    grab[0].close();
    grab[1].close();
}


void ofApp::endCurrentScene() { scene[curScene]->disable(); }
void ofApp::nextScene()
{
    curScene = (curScene + 1)%3;
    scene[curScene]->enable();
    countdownTimer = FRAMES_PER_SCENE;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
	ofSetFrameRate(60);
	ofSetWindowTitle("fablesViewer");
	ofHideCursor();
    
    // setup GUI
    devices = grab[0].listDevices();
	for (int i = 0; i < devices.size(); i++) {
		ofLog() << i << ": " << devices[i].serialID;
	}
    debug = false;
    
    loadBtn.addListener(this, &ofApp::loadSettings);
    saveBtn.addListener(this, &ofApp::saveSettings);
    refreshCamBtn.addListener(this, &ofApp::refreshCams);
    
    GUI = new ofxPanel();
    GUI->setup("Settings");
    
    guiAdmin.setup("Admin");
    guiAdmin.add(saveBtn.setup("Save settings"));
    guiAdmin.add(loadBtn.setup("Load settings"));
    GUI->add(&guiAdmin);
    
    guiCamera.setup("Camera");
    guiCamera.add(scaleCams.setup("Camera scale", 1.0, 0.25, 2.0));
    guiCamera.add(toggleCam[0].setup("Toggle Cam A", 0, 0, (int)devices.size()-1));
    guiCamera.add(toggleCam[1].setup("Toggle Cam B", CLAMP(1, 0, (int)devices.size()-1), 0, (int)devices.size()-1));
    guiCamera.add(refreshCamBtn.setup("Refresh cams"));
    guiCamera.add(swapCams.setup("Swap cams", false));
    GUI->add(&guiCamera);
    
    // Work out various dimensions
    center = ofVec2f(ofGetWidth()*0.5, ofGetHeight()*0.5);
    portW = (int)SCREEN_W*0.5;
    portH = SCREEN_H;
    
    // setup cameras
#ifndef TEST_VID
    // determine offsets
    offX = 0.5*(CAM_RES_X - portW);
    offY = 0.5*(CAM_RES_Y - portH);
#else
    testVid.load("test.mov");
    testVid.play();
    
    offX = 0.5*(CAM_RES_X*0.5 - portW);
    offY = 0.5*(CAM_RES_Y - portH);
#endif
    
    
    rawTexture.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    buffer.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    
    // load Passes
    sketch = new SketchPass();
    bitshift = new BSPass();
    points = new PointPass();
    scene[0] = bitshift;
    scene[1] = bitshift;
    scene[2] = bitshift;
    
    // first scene!
    bitshift->enable();
    
    GUI->loadFromFile("settings.xml");
    
#ifndef TEST_VID
    for (int i = 0; i < 2; i++) {
        grab[i].setDeviceID(toggleCam[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
#endif
    
    countdownTimer = FRAMES_PER_SCENE;
    cdRatio = 1;
    curScene = 0;
    ofAddListener(timerEndEvent, this, &ofApp::endCurrentScene);
    for (int i = 0; i < 3; i++)
        ofAddListener(scene[i]->sceneOverEvent, this, &ofApp::nextScene);
    
}

//--------------------------------------------------------------
void ofApp::loadSettings()
{
    GUI->loadFromFile("settings.xml");
}

void ofApp::saveSettings()
{
    GUI->saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::refreshCams()
{
    for (int i = 0; i < 2; i++) {
        grab[i].close();
        grab[i].setDeviceID(toggleCam[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
#ifndef TARGET_OSX
	if (ofGetFrameNum() == 1) ofSetFullscreen(true);
#endif

    // Timing stuff
    if (countdownTimer > 0) {
        countdownTimer--;
        cdRatio = float(countdownTimer)/FRAMES_PER_SCENE;
        if (countdownTimer == 0) ofNotifyEvent(timerEndEvent);
    }
    
    bool newFrames = false;
    
#ifndef TEST_VID
    // update grabbers and pass textures to buffer
    
    for (int i = 0; i < 2; i++) {
        grab[i].update();
        
        if (grab[i].isFrameNew()) {
            rawTexture.begin();
            ofPushMatrix();
            ofSetColor(255);
            if (!swapCams) ofTranslate(i*portW, 0);
            else ofTranslate(portW*(1 - i), 0);
            grab[i].getTexture().drawSubsection(0, 0, portW, portH, offX, offY, portW, portH);
            ofPopMatrix();
            rawTexture.end();
            newFrames = true;
        }
    }
    
#else
    testVid.update();
    if (testVid.isFrameNew()) {
        newFrames = true;
        rawTexture.begin();
        ofSetColor(255);
        testVid.draw(0, 0, SCREEN_W, SCREEN_H);
        rawTexture.end();
    }
#endif
    
    if (newFrames) {
        bitshift->runUpdate(rawTexture.getTexture());
        sketch->runUpdate(rawTexture.getTexture());
        points->runUpdate(rawTexture.getTexture());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofPushMatrix();
    ofTranslate(center);
    ofScale(scaleCams, scaleCams, 1);
    
    ofSetColor(255);
    ofFill();
    ofDrawRectangle(-SCREEN_W*0.5, -SCREEN_H*0.5, SCREEN_W, SCREEN_H);
    
    // render cam output
    ofSetColor(255);
    rawTexture.draw(-SCREEN_W*0.5, -SCREEN_H*0.5);
    
    // render current pass here
    sketch->draw();
    bitshift->draw();
    points->draw();
    
    ofSetColor(128, 200 + 55*sin(ofGetFrameNum()*0.1*cdRatio));
    ofDrawRectangle(-SCREEN_W*0.5, 100-SCREEN_H*0.5, portW*cdRatio, 3);
    ofDrawRectangle(0, 100-SCREEN_H*0.5, portW*cdRatio, 3);
    
    ofPopMatrix();
    
    if (debug) {
        ofSetColor(255);
        GUI->draw();
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 0, 14);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'd') {
		debug = !debug;
		if (debug) ofShowCursor();
		else ofHideCursor();
	}
    if (key == 'f') ofToggleFullscreen();
    if (key == 'p') ofSaveFrame();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	swapCams = !swapCams;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    center = ofVec2f(w*0.5, h*0.5);
}
