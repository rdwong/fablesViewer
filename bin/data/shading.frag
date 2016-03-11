#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
//uniform sampler2DRect hatch1;
//uniform sampler2DRect hatch2;
//uniform sampler2DRect hatch3;
//uniform sampler2DRect hatch4;

uniform float threshold;

varying vec2 texCoordVarying;

void main()
{
    vec4 px = texture2DRect(tex, texCoordVarying);
    float intensity = (px.r + px.g + px.b)/3.0;
    
    if (intensity > threshold) intensity = 1.0;
    else {
        float upval = (intensity)/threshold;
        intensity = floor(4.0*upval);
        intensity /= 4.0;
    }
    
    float alpha = 1 - clamp(intensity, 0.0, 1.0);
    
    vec4 color = vec4(px.r*0.75, px.g*0.75, px.b*0.75, alpha);
    
    gl_FragColor = color;
}