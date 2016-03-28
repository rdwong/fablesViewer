#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect prev;
uniform sampler2DRect next;
uniform float threshold;
varying vec2 texCoordVarying;


void main()
{
    // Get difference
    vec4 pre = texture2DRect(prev, texCoordVarying);
    vec4 nex = texture2DRect(next, texCoordVarying);
    float difference = abs(nex.r - pre.r) + abs(nex.g - pre.g) + abs(nex.b - pre.b);
    
    float alpha = 0.0;
    if (difference > threshold) {
        alpha = 1.0;//difference(texCoordVarying) - threshold;
    }
    
    vec4 color = vec4(0.0, 0.0, 0.0, alpha);
    gl_FragColor = color;
}