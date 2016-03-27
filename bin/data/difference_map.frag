#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect prev;
uniform sampler2DRect next;
uniform float threshold;
varying vec2 texCoordVarying;

// pseudo noise
float getValue(vec2 co)
{
    return 0.25*fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

// total color difference
float difference(in vec2 coords) {
    vec4 pre = texture2DRect(prev, coords);
    vec4 nex = texture2DRect(next, coords);
    return abs(nex.r - pre.r) + abs(nex.g - pre.g) + abs(nex.b - pre.b);
}

void main()
{
    float alpha = 0.0;
    if (difference(texCoordVarying) > threshold) {
        alpha = 1.0;//difference(texCoordVarying) - threshold;
    }
    //alpha = clamp(alpha, 0, 1.0);
    
    vec4 color = vec4(0.0, 0.0, 0.0, alpha);
    gl_FragColor = color;
}