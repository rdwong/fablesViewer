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

#define FADESPEED   0.05

class Pass
{
    
protected:
    
    bool active;
    bool fade;
    
    virtual void endActions() {}
    virtual void startActions() {}
    
public:
    
    float alpha;
    
    ofEvent<void> sceneOverEvent;
    
    Pass()
    {
        active = false;
        fade = false;
        alpha = 0;
    }
    
    void runUpdate(ofTexture & raw)
    {
        if (!active) return;
        
        if (!fade) {
            alpha += (1 - alpha)*FADESPEED;
        } else {
            alpha *= (1 - FADESPEED);
            if (alpha*255 < 1) {
                active = false;
                fade = false;
                alpha = 0;
                ofNotifyEvent(sceneOverEvent);
            }
        }
            
        update(raw);
    }
    
    void draw()
    {
        if (!active) return;
        ofSetColor(255, floor(alpha*255.0));
        render();
    }
    
    virtual void update(ofTexture & raw)=0;
    virtual void render()=0;
    
    void enable() { startActions(); active = true; }
    void disable() { endActions(); fade = true; }
    
};

#endif
