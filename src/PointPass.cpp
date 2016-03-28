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
    pointPanel.add(interval.setup("Interval", 0.1, 0.0, 0.5));
}

void PointPass::update(ofTexture & raw)
{
    fbo.begin();
    points.begin();
    points.setUniform1f("interval", interval);
    points.setUniformTexture("tex", raw, 0);
    canvas(SCREEN_W, SCREEN_H);
    points.end();
    fbo.end();
}

void PointPass::render()
{
    fbo.draw(0, 0);
}