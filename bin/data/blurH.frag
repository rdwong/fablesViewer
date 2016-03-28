#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect src_tex_unit0;
uniform float amt;
uniform float radius;
varying vec2 texCoordVarying;

void main(void) {
    vec4 color = radius * texture2DRect(src_tex_unit0, texCoordVarying);
    float parts = radius;
    float level = texture2DRect(src_tex_unit0, texCoordVarying).r;
    
    for (float i = 1.0; i <= radius-1; i++) {
        
        vec2 coord = texCoordVarying + vec2(amt*(i - radius), 0.0);
        vec4 px1 = texture2DRect(src_tex_unit0, coord);
        //if (px1.r < level) {
            color += i * px1;
            parts += i;
        //}
        
        coord = texCoordVarying + vec2(amt*i, 0.0);
        vec4 px2 = texture2DRect(src_tex_unit0, coord);
        //if (px2.r < level) {
            color += i * px2;
            parts += i;
        //}
    }
    
    color /= parts;
    gl_FragColor = color;
}