//
//  Pass.h
//  fablesViewer
//
//  Created by Richard Wong on 11/03/2016.
//
//

#ifndef fablesViewer_Pass_h
#define fablesViewer_Pass_h

#include "Globals.h"

class Pass
{
    
public:
    
    bool active;
    
    Pass()
    {
        active = false;
    }
    
    void runUpdate(ofTexture & raw)
    {
        if (!active) return;
        update(raw);
    }
    
    virtual void update(ofTexture & raw)=0;
    virtual void render()=0;
    
    void toggle() { active = !active; }
    void toggle(bool state) { active = state; }
    
};

#endif
