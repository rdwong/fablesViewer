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
    
    void draw()
    {
        if (!active) return;
        render();
    }
    
    virtual void update(ofTexture & raw)=0;
    virtual void render()=0;
    
    void enable() { startActions(); active = true; }
    void disable() { endActions(); active = false; }
    
protected:
    
    virtual void endActions() {}
    virtual void startActions() {}
};

#endif
