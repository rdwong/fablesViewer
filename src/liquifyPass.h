//
//  liquifyPass.h
//  fablesViewer
//
//  Created by Richard Wong on 1/04/2016.
//
//

#ifndef __fablesViewer__liquifyPass__
#define __fablesViewer__liquifyPass__

#include "Pass.h"

#define NUM_STEPS

class LiquifyPass : public Pass
{
public:
    
    bool bFirstframe;
    
    RGBFbo fbo;
    
    ofTexture prevFrame;
    
    ofShader liquify;
    
    LiquifyPass();
    
    void update(ofTexture & raw);
    void render();
    
};
#endif /* defined(__fablesViewer__liquifyPass__) */
