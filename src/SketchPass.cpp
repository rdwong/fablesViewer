//
//  SketchPass.cpp
//  fablesViewer
//
//  Created by Richard Wong on 11/03/2016.
//
//

#include "SketchPass.h"

SketchPass::SketchPass()
{
    
    baseTex = 0;
    
    ofDirectory dir; dir.listDir("hatches");
    for (int i = 0; i < dir.size(); i++)
        hatches.push_back(ofImage("hatches/" + ofToString(i) + ".png"));
    
    guiShaderSketch.setup("Shader-Sketch");
    guiShaderSketch.add(shadeThreshold.setup("Shading thresh", 0.02, 0.0, 1.0));
    guiShaderSketch.add(outlineThreshold.setup("Outline thresh", 0.02, 0.0, 1.0));
    guiShaderSketch.loadFromFile("settings.xml");
    GUI->add(&guiShaderSketch);
    
    shadeFbo.setAnchorPercent(0.5, 0.5);
    outlineFbo.setAnchorPercent(0.5, 0.5);
    
    // load shaders
    outlineShader.load("outline");
    shadingShader.load("shading");
    
}

void SketchPass::update(ofTexture & raw)
{
    // make shading pass with buffer
    shadeFbo.begin();
    ofClear(255);
    
    shadingShader.begin();
    shadingShader.setUniformTexture("tex", raw, 0);
    shadingShader.setUniformTexture("hatch1", hatches[getTex(0)].getTexture(), 1);
    shadingShader.setUniformTexture("hatch2", hatches[getTex(1)].getTexture(), 2);
    shadingShader.setUniformTexture("hatch3", hatches[getTex(2)].getTexture(), 3);
    shadingShader.setUniformTexture("hatch4", hatches[getTex(3)].getTexture(), 4);
    shadingShader.setUniform1f("threshold", shadeThreshold);
    canvas(SCREEN_W, SCREEN_H);
    shadingShader.end();
    
    shadeFbo.end();
    
    // make outline pass with buffer
    outlineFbo.begin();
    ofClear(0,0,0,0);
    
    outlineShader.begin();
    outlineShader.setUniformTexture("tex", raw, 0);
    outlineShader.setUniform1f("threshold", outlineThreshold);
    canvas(SCREEN_W, SCREEN_H);
    outlineShader.end();
    
    outlineFbo.end();
    
    if (ofGetFrameNum()%2 == 0) baseTex = (baseTex+1)%int(hatches.size());
}

void SketchPass::render()
{
    shadeFbo.draw(0, 0);
    outlineFbo.draw(0, 0);
}


