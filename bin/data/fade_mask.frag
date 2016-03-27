#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect bitshift;
uniform sampler2DRect fademap;
varying vec2 texCoordVarying;

void main()
{
    vec4 color = texture2DRect(bitshift, texCoordVarying);
    vec4 fadepx = texture2DRect(fademap, texCoordVarying);
    
    if (fadepx.r <= 0.99) {
        color.r = color.r*fadepx.r + (1 - fadepx.r);
        color.g = color.g*fadepx.g + (1 - fadepx.g);
        color.b = color.b*fadepx.b + (1 - fadepx.b);
    }
    
    gl_FragColor = color;
}