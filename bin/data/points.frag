#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform float interval;

varying vec2 texCoordVarying;

void main()
{
    vec4 px = texture2DRect(tex, texCoordVarying);
    float intensity = (px.r + px.g + px.b)/3.0;
    
    float level = floor(intensity/interval);
    float value = level*interval;
    
    vec4 color = vec4(value, value, value, 1.0);
    
    gl_FragColor = color;
}