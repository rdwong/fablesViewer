//
//  BlurShaderWrapper.cpp
//  fablesViewer
//
//  Created by Richard Wong on 26/03/2016.
//
//

#include "BlurShaderWrapper.h"

void BlurShaders::setup(float w, float h) {
    
    fbo1.allocate(w,h);
    fbo2.allocate(w,h);
    
    vShader.load("blurV");
    hShader.load("blurH");
}

void BlurShaders::begin(int amount, float radius, int iterations) {
    this->amount = amount;
    this->iterations = iterations;
    this->radius = radius;
    
    //start 'recording' the user's drawing commands to the fbo
    fbo1.begin();
}

void BlurShaders::end(bool draw) {
    fbo1.end();
    for (int i=0; i<iterations; i++) {
        
        //apply horizontal blur to fbo1 and put the result in fbo2
        fbo2.begin();
        hShader.begin();
        hShader.setUniform1f("amt", amount);
        hShader.setUniform1f("radius", radius);
        fbo1.draw(0,0);
        hShader.end();
        fbo2.end();
        
        //apply vertical blur to fbo2 and put this back in fbo1
        fbo1.begin();
        vShader.begin();
        vShader.setUniform1f("amt", amount);
        vShader.setUniform1f("radius", radius);
        fbo2.draw(0,0);
        hShader.end();
        fbo1.end();
    }
    
    if (draw) fbo1.draw(0,0);
}

