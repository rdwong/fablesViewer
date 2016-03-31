	//
//  BSPass.hpp
//  fablesViewer
//
//  Created by Richard Wong on 12/03/2016.
//
//

#ifndef BSPass_h
#define BSPass_h

#include "Pass.h"
#include "BlurShaderWrapper.h"

#define NUM_STEPS

class BSPass : public Pass
{
public:
    
    bool bFirstframe;
    
    RGBAFbo diffFrame;
    RGBFbo diffBuffer;
    RGBFbo diffFadeFbo;
    RGBFbo diffFadeBuffer;
    //RGBFbo bitshiftFbo;
    RGBFbo fbo;
    
    ofTexture prevFrame;
    
    ofShader difference_map;
    ofShader fade_mask;
    
    BlurShaders blur;
    
    ofxPanel BSPanel;
    ofxFloatSlider fadeRatio;
    ofxFloatSlider blurAmount;
    ofxFloatSlider blurRadius;
    ofxFloatSlider diffThreshold;
    
    BSPass();
    
    void update(ofTexture & raw);
    void render();
    
};

#endif /* BSPass_hpp */
