#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform float interval;

varying vec2 texCoordVarying;

const float threshold = 0.3;

void main()
{
    vec4 px = texture2DRect(tex, texCoordVarying);
    float intensity = (px.r + px.g + px.b)/3.0;
    
    if (intensity > threshold) intensity = 1.0;
    else {
        float upval = (intensity)/threshold;
        intensity = floor(6.0*upval);
        float level = int(mod(intensity, 4.0));
        intensity /= 6.0;
    }
    
    float value = clamp(intensity, 0.0, 1.0);
    vec4 color = vec4(value, value, value, 1.0);
    
    gl_FragColor = color;
}