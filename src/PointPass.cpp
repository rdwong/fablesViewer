//
//  PointPass.cpp
//  fablesViewer
//
//  Created by Richard Wong on 28/03/2016.
//
//

#include "PointPass.hpp"

PointPass::PointPass()
{
    points.load("points");
    fbo.setAnchorPercent(0.5, 0.5);
    
    GUI->add(pointPanel.setup("Point Pass"));
    pointPanel.add(threshold.setup("Threshold", 0.3, 0.0, 0.8));
    pointPanel.add(tileSize.setup("Tile size", 5, 1.0, 10.0));
}

void PointPass::update(ofTexture & raw)
{
    fbo.begin();
    points.begin();
    points.setUniform1f("threshold", threshold);
    points.setUniform1f("tileSize", tileSize);
    points.setUniform1f("time", ofGetFrameNum()*0.1);
    points.setUniformTexture("tex", raw, 0);
    canvas(SCREEN_W, SCREEN_H);
    points.end();
    fbo.end();
}

void PointPass::render()
{
    fbo.draw(0, 0);
}