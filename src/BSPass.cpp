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
    
    // setup fbos
    blur.setup(SCREEN_W, SCREEN_H);
    
    // Set 50% anchor for main output
    fbo.setAnchorPercent(0.5, 0.5);
    //diffFadeFbo.setAnchorPercent(0.5, 0.5);
    //bitshiftFbo.setAnchorPercent(0.5, 0.5);
    
    difference_map.load("difference_map");
    fade_mask.load("fade_mask");
    
    BSPanel.setup("Bitshift");
    BSPanel.add(diffThreshold.setup("Diff threshold", 0.1, 0, 2.0));
    BSPanel.add(blurAmount.setup("Blur amount", 5.0, 0.0, 10.0));
    BSPanel.add(blurRadius.setup("Blur radius", 5.0, 0.0, 10.0));
    BSPanel.add(fadeRatio.setup("Fade Ratio", 128, 0, 255));
    GUI->add(&BSPanel);
    
}

void BSPass::update(ofTexture & raw)
{
    
    // 1a --- Difference Pass
    diffFrame.begin();
    ofClear(0,0,0,0);
    if (!bFirstframe) {
        ofSetColor(255);
        difference_map.begin();
        difference_map.setUniformTexture("prev", diffBuffer.getTexture(), 0);
        difference_map.setUniformTexture("next", raw, 1);
        difference_map.setUniform1f("threshold", diffThreshold);
        canvas(SCREEN_W, SCREEN_H);
        difference_map.end();
    }
    diffFrame.end();
    
    // 2a --- Fade Difference Pass
    diffFadeFbo.begin();
    ofSetColor(255);
    if (bFirstframe) ofClear(255);
    else diffFadeBuffer.draw(0, 0);
    diffFrame.draw(0, 0);
    diffFadeFbo.end();
    
    // 2b --- Buffer the fade for next round
    diffFadeBuffer.begin();
    ofClear(255);
    ofSetColor(255, 255 - fadeRatio);
    diffFadeFbo.draw(0, 0);
    diffFadeBuffer.end();
    
    // 3 -- Blur fadeMask
    blur.begin(blurAmount, blurRadius, 3);
    diffFadeFbo.draw(0, 0);
    blur.end(false);
    
    // 4 --- Bitshift
    bitshiftFbo.begin();
    if (bFirstframe) {
        ofSetColor(255,255,255,255);
        ofClear(0,0,0,255);
        raw.draw(0, 0);
    }
    ofSetColor(255,255,255,fadeRatio);
    raw.draw(0, 0);
    bitshiftFbo.end();
    
    //5 --- composite pass
    fbo.begin();
    if (bFirstframe) {
        ofClear(255);
        ofSetColor(255);
        raw.draw(0, 0);
    } else {
        fade_mask.begin();
        fade_mask.setUniformTexture("bitshift", bitshiftFbo.getTexture(), 0);
        fade_mask.setUniformTexture("fademap", blur.getTexture(), 1);
        fade_mask.setUniform1f("iGlobalTime", ofGetFrameNum());
        canvas(SCREEN_W, SCREEN_H);
        fade_mask.end();
    }
    fbo.end();
    
    // Deny first frame boolean
    if (bFirstframe) bFirstframe = false;
    
    // End -- -Save difference frame for cross-checking
    diffBuffer.begin();
    ofSetColor(255);
    raw.draw(0, 0);
    diffBuffer.end();
    
}

void BSPass::render()
{
    ofSetColor(255);
    fbo.draw(0, 0);
    //diffFadeFbo.draw(-SCREEN_W*0.5, -SCREEN_H*0.5);
}