#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    
    outlineShader.load("outline");
    shadingShader.load("shading");
    
    portW = (int)SCREEN_W*0.5;
    portH = SCREEN_H;
    
    devices = grab[0].listDevices();
    
    debug = false;
    
    loadBtn.addListener(this, &ofApp::loadSettings);
    saveBtn.addListener(this, &ofApp::saveSettings);
    refreshCamBtn.addListener(this, &ofApp::refreshCams);
    
    gui.setup();
    
    guiAdmin.setup("Admin");
    guiAdmin.add(saveBtn.setup("Save settings"));
    guiAdmin.add(loadBtn.setup("Load settings"));
    gui.add(&guiAdmin);
    
    guiCamera.setup("Camera");
    guiCamera.add(scaleCams.setup("Camera scale", 1.0, 0.25, 2.0));
    guiCamera.add(toggleCam[0].setup("Toggle Cam A", 0, 0, (int)devices.size()-1));
    guiCamera.add(toggleCam[1].setup("Toggle Cam B", CLAMP(1, 0, (int)devices.size()-1), 0, (int)devices.size()-1));
    guiCamera.add(refreshCamBtn.setup("Refresh cams"));
    guiCamera.add(swapCams.setup("Swap cams", false));
    gui.add(&guiCamera);
    
    guiShaderSketch.setup("Shader-Sketch");
    guiShaderSketch.add(shadeThreshold.setup("Shading thresh", 0.02, 0.0, 1.0));
    guiShaderSketch.add(outlineThreshold.setup("Outline thresh", 0.02, 0.0, 1.0));
    guiShaderSketch.loadFromFile("settings.xml");
    gui.add(&guiShaderSketch);
    
    for (int i = 0; i < 2; i++) {
        grab[i].setDeviceID(toggleCam[i]);
        grab[i].setup(CAM_RES_X, CAM_RES_Y);
    }
    
    offX = 0.5*(grab[0].getWidth() - portW);
    offY = 0.5*(grab[0].getHeight() - portH);
    
    rawTexture.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    buffer.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    
    shadeFbo.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    outlineFbo.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    
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
    
    ofPushMatrix();
    ofTranslate(SCREEN_W*0.5, SCREEN_H*0.5);
    ofScale(scaleCams, scaleCams, 1);
    ofTranslate(-SCREEN_W*0.5, -SCREEN_H*0.5);
    
    ofSetColor(0,0,0,128);
    ofDrawLine(-1, -1, SCREEN_W+2, -1);
    ofDrawLine(-1, SCREEN_H+2, SCREEN_W+2, SCREEN_H+2);
    
    ofSetColor(255);
    shadeFbo.draw(0, 0);
    outlineFbo.draw(0, 0);
    
    ofPopMatrix();
    
    if (debug) {
        ofSetColor(255);
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'd') debug = !debug;
    if (key == 'f') ofToggleFullscreen();
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
