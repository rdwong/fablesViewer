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

class BSPass : public Pass
{
public:
    
    ofFbo buffer;
    ofFbo fbo;
    bool bFirstframe;
    
    ofxPanel BSPanel;
    ofxFloatSlider fadeRatio;
    
    BSPass();
    
    void update(ofTexture & raw);
    void render();
    
};

#endif /* BSPass_hpp */
