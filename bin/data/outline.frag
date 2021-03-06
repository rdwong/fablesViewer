#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform float threshold;

varying vec2 texCoordVarying;

// averaged pixel intensity from 3 color channels
float avg_intensity(in vec2 coords) {
    vec4 pix = texture2DRect(tex, coords);
    return (pix.r + pix.g + pix.b)/3.0;
}

// returns pixel color
float IsEdge(in vec2 coords){
    
    float pix[9];
    int k = -1;
    
    // read neighboring pixel intensities
    for (int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            k++;
            pix[k] = avg_intensity(coords + vec2(float(i), float(j)));
        }
    }
    
    // average color differences around neighboring pixels
    float delta = (abs(pix[1]-pix[7]) + abs(pix[5]-pix[3]) + abs(pix[0]-pix[8]) + abs(pix[2]-pix[6]))/4.0;
    delta = clamp(2.5*delta, 0.0, 1.0);
    if (delta > threshold) delta = delta*0.3 + 0.7;
    
    return delta;
}

void main()
{
    vec4 color = vec4(0.05,0.05,0.05,0.0);
    color.a = IsEdge(texCoordVarying);
    gl_FragColor = color;
}