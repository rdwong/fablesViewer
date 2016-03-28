//
//  SketchPass.h
//  fablesViewer
//
//  Created by Richard Wong on 11/03/2016.
//
//

#ifndef __fablesViewer__SketchPass__
#define __fablesViewer__SketchPass__

#include "Pass.h"

class SketchPass : public Pass
{
    int getTex(int seq) { return (seq+baseTex)%int(hatches.size()); }
    int baseTex;
    
public:
    
    vector<ofImage> hatches;
    
    // Shader Stuff
    ofShader outlineShader;
    ofShader shadingShader;
    RGBAFbo shadeFbo;
    RGBAFbo outlineFbo;
    
    ofxPanel guiShaderSketch;
    ofxFloatSlider shadeThreshold;
    ofxFloatSlider outlineThreshold;
    
    SketchPass();
    
    void update(ofTexture & raw);
    void render();
    
};

#endif /* defined(__fablesViewer__SketchPass__) */
