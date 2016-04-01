//
//  liquifyPass.cpp
//  fablesViewer
//
//  Created by Richard Wong on 1/04/2016.
//
//

#include "liquifyPass.h"

LiquifyPass::LiquifyPass()
{
    bFirstframe = true;
    
    // Set 50% anchor for main output
    fbo.setAnchorPercent(0.5, 0.5);
    liquify.load("liquify");
}

void LiquifyPass::update(ofTexture & raw)
{
    
    fbo.begin();
    ofClear(255);
    if (bFirstframe) {
        raw.draw(0, 0);
        bFirstframe = false;
    } else {
        ofSetColor(255);
        liquify.begin();
        liquify.setUniformTexture("fademap", raw, 1);
        liquify.setUniform1f("time", ofGetFrameNum());
        canvas(SCREEN_W, SCREEN_H);
        liquify.end();
    }
    fbo.end();
    
}

void LiquifyPass::render()
{
    fbo.draw(0, 0);
}
