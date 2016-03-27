//
//  BlurShaderWrapper.hpp
//  fablesViewer
//
//  Created by Richard Wong on 26/03/2016.
//
//

#ifndef BlurShaderWrapper_hpp
#define BlurShaderWrapper_hpp

#pragma once

#include "ofMain.h"

class BlurShaders {
public:
    
    void setup(float w, float h);
    void begin(int amount=5, float radius=4.0, int iterations=2);
    void end(bool draw=true);
    //void draw(float x=0, float y=0, float w=0, float h=0);
    
    int iterations, amount;
    float radius;
    
    ofFbo fbo1,fbo2;
    ofShader hShader, vShader;
    ofTexture & getTexture() { return fbo1.getTexture(); }
    
};

#endif /* BlurShaderWrapper_hpp */
