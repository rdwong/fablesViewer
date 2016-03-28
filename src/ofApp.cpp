#include "ofApp.h"

void ofApp::ofExit()
{
    grab[0].close();
    grab[1].close();
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    
    // setup GUI
    devices = grab[0].listDevices();
    
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
    //sketch->enable();
    
    bitshift = new BSPass();
    //bitshift->enable();
    
    points = new PointPass();
    points->enable();
    
    curPass = 0;
    
    GUI->loadFromFile("settings.xml");
    refreshCams();
    
#ifndef TEST_VID
    for (int i = 0; i < 2; i++) {
        grab[i].setDeviceID(toggleCam[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
#endif
    
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
    ofDrawRectangle(0, 0, SCREEN_W, SCREEN_H);
    
    ofPushMatrix();
    ofTranslate(center);
    ofScale(scaleCams, scaleCams, 1);
    
    ofSetColor(255);
    ofFill();
    ofDrawRectangle(-SCREEN_W*0.5, -SCREEN_H*0.5, SCREEN_W, SCREEN_H);
    
    ofSetColor(255);
    
    // render current pass here
    rawTexture.draw(-SCREEN_W*0.5, -SCREEN_H*0.5);
    //sketch->render();
    //bitshift->render();
    //points->render();
    
    ofPopMatrix();
    
    if (debug) {
        ofSetColor(255);
        GUI->draw();
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 0, 14);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'd') debug = !debug;
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
