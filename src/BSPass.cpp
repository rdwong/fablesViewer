//
//  BSPass.cpp
//  fablesViewer
//
//  Created by Richard Wong on 12/03/2016.
//
//

#include "BSPass.h"

BSPass::BSPass()
{
    bFirstframe = true;
    
    buffer.allocate(SCREEN_W, SCREEN_H, GL_RGBA);
    buffer.setAnchorPercent(0.5, 0.5);
    
    fbo.allocate(SCREEN_W, SCREEN_H, GL_RGB);
    fbo.setAnchorPercent(0.5, 0.5);
    
    BSPanel.setup("Bitshift");
    BSPanel.add(fadeRatio.setup("Fade Ratio", 128, 0, 255));
    GUI->add(&BSPanel);
}

void BSPass::update(ofTexture & raw)
{
    
    fbo.begin();
    
    if (bFirstframe) {
        ofSetColor(255,255,255,255);
        ofClear(0,0,0,255);
        raw.draw(0, 0);
        bFirstframe = false;
    }
    
    // update bitshift from raw
    ofSetColor(255,255,255,fadeRatio);
    raw.draw(0, 0);
    fbo.end();
    
}

void BSPass::render()
{
    fbo.draw(0, 0);
}