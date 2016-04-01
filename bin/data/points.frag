#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform float threshold;
uniform float tileSize;
uniform float time;

varying vec2 fragCoord;

vec2 get_source_pos()
{
    float xp = tileSize*floor(fragCoord.x/tileSize) + tileSize*0.5;
    float yp = tileSize*floor(fragCoord.y/tileSize) + tileSize*0.5;
    return vec2(xp, yp);
}

float dist(vec2 a, vec2 b)
{
    vec2 c = a - b;
    return sqrt(c.x*c.x + c.y*c.y);
}

void main()
{
    // set default color
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    
    // get source pos and distance from src pos
    vec2 srcPos = get_source_pos();
    
    // get source intensity
    vec4 px = texture2DRect(tex, srcPos);
    float intensity = (px.r + px.g + px.b)/3.0;
    if (intensity > threshold) intensity = 1.0;
    else {
        float upval = (intensity)/threshold;
        intensity = (floor(5.0*upval))/5.0;
    }
    float spotSize = tileSize*0.5*(1 - intensity);
    
    // check if px is within range
    float d = dist(srcPos, fragCoord);
    if (d < spotSize) {
        color = vec4(1-(1-px.r)*(1-px.r), 1-(1-px.g)*(1-px.g), 1-(1-px.b)*(1-px.b), 1.0);
    }
    
    gl_FragColor = color;
    
}