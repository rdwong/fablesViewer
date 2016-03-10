#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    
    outlineShader.load("outline");
    shadingShader.load("shading");
    
    portW = (int)SCREEN_W*0.5;
    portH = SCREEN_H;
    
    devices = grab[0].listDevices();
    
    for (int i = 0; i < 2; i++) {
        deviceID[i] = MIN(i, devices.size()-1);
        deviceIDString[i] = "Camera ID: " + ofToString(deviceID[i]);
        grab[i].setDeviceID(deviceID[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
    
    offX = 0.5*(grab[0].getWidth() - portW);
    offY = 0.5*(grab[0].getHeight() - portH);
    
    rawTexture.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    buffer.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    
    shadeFbo.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    outlineFbo.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    
    debug = false;
    
    loadBtn.addListener(this, &ofApp::loadSettings);
    saveBtn.addListener(this, &ofApp::saveSettings);
    
    toggleCamADevice.addListener(this, &ofApp::toggleCamAID);
    toggleCamBDevice.addListener(this, &ofApp::toggleCamBID);
    refreshCamBtn.addListener(this, &ofApp::refreshCams);
    
    gui.setup();
    gui.add(saveBtn.setup("Save settings"));
    gui.add(loadBtn.setup("Load settings"));
    gui.add(toggleCamADevice.setup(deviceIDString[0]));
    gui.add(toggleCamBDevice.setup(deviceIDString[1]));
    gui.add(refreshCamBtn.setup("Refresh cams"));
    gui.add(swapCams.setup("Swap cams", false));
    
    gui.add(shadeThreshold.setup("Shading thresh", 0.02, 0.0, 0.5));
    gui.add(outlineThreshold.setup("Outline thresh", 0.02, 0.0, 0.7));
    gui.loadFromFile("settings.xml");
    
}

//--------------------------------------------------------------
void ofApp::loadSettings()
{
    gui.loadFromFile("settings.xml");
}

void ofApp::saveSettings()
{
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::toggleCamAID()
{
    deviceID[0] = (deviceID[0]+1)%devices.size();
    deviceIDString[0] = "Camera ID: " + ofToString(deviceID[0]);
}

void ofApp::toggleCamBID()
{
    deviceID[1] = (deviceID[1]+1)%devices.size();
    deviceIDString[1] = "Camera ID: " + ofToString(deviceID[1]);
}

void ofApp::refreshCams()
{
    for (int i = 0; i < 2; i++) {
        grab[i].close();
        grab[i].setDeviceID(deviceID[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update grabbers and pass textures to buffer
    for (int i = 0; i < 2; i++) {
        grab[i].update();
        
        if (grab[i].isFrameNew()) {
            rawTexture.begin();
            ofPushMatrix();
            
            if (!swapCams) ofTranslate(i*portW, 0);
            else ofTranslate(portW*(1 - i), 0);
            grab[i].getTexture().drawSubsection(0, 0, portW, portH, offX, offY, portW, portH);
            ofPopMatrix();
            rawTexture.end();
        }
    }
    
    // make shading pass with buffer
    shadeFbo.begin();
    ofClear(0,0,0,0);
    
    shadingShader.begin();
    shadingShader.setUniformTexture("tex", rawTexture.getTexture(), 0);
    shadingShader.setUniform1f("threshold", shadeThreshold);
    canvas(SCREEN_W, SCREEN_H);
    shadingShader.end();
    
    shadeFbo.end();
    
    // make outline pass with buffer
    outlineFbo.begin();
    ofClear(0,0,0,0);
    
    outlineShader.begin();
    outlineShader.setUniformTexture("tex", rawTexture.getTexture(), 0);
    outlineShader.setUniform1f("threshold", outlineThreshold);
    canvas(SCREEN_W, SCREEN_H);
    outlineShader.end();
    
    outlineFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    shadeFbo.draw(0, 0);
    outlineFbo.draw(0, 0);
    
    if (debug) {
        ofSetColor(255);
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'd') debug = !debug;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
