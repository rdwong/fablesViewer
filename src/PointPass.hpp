//
//  PointPass.hpp
//  fablesViewer
//
//  Created by Richard Wong on 28/03/2016.
//
//

#ifndef PointPass_hpp
#define PointPass_hpp

#include "Pass.h"

class PointPass : public Pass
{
public:
    
    ofShader points;
    RGBFbo fbo;
    
    ofxPanel pointPanel;
    ofxFloatSlider interval;
    
    PointPass();
    
    void update(ofTexture & raw);
    void render();
    
};

#endif /* PointPass_hpp */
