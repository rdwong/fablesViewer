#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform sampler2DRect hatch1;
uniform sampler2DRect hatch2;
uniform sampler2DRect hatch3;
uniform sampler2DRect hatch4;

uniform float threshold;

varying vec2 texCoordVarying;

void main()
{
    vec4 px = texture2DRect(tex, texCoordVarying);
    float intensity = (px.r + px.g + px.b)/3.0;
    
    int level = 0;
    
    if (intensity > threshold) intensity = 1.0;
    else {
        float upval = (intensity)/threshold;
        intensity = floor(6.0*upval);
        level = int(mod(intensity, 4.0));
        intensity /= 6.0;
    }
    
    float alpha = 1 - clamp(intensity, 0.0, 1.0);
    
    vec4 hatchPx = vec4(px.r, px.g, px.b, 1.0);
    if (level == 0) hatchPx = texture2DRect(hatch1, texCoordVarying);
    else if (level == 1) hatchPx = texture2DRect(hatch2, texCoordVarying);
    else if (level == 2) hatchPx = texture2DRect(hatch3, texCoordVarying);
    else if (level == 3) hatchPx = texture2DRect(hatch4, texCoordVarying);
    
    alpha *= (1 - hatchPx.r);
    
    vec4 color = vec4(hatchPx.r, hatchPx.g, hatchPx.b, alpha*0.9);
    
    gl_FragColor = color;
}