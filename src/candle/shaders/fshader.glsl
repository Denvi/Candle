#version 110
#define DATA_TYPE_LINE 0
#define DATA_TYPE_DASH 1
#define DATA_TYPE_DASH_DOT 2
#define DATA_TYPE_POINT 3
#define DATA_TYPE_TRIANGLE 4

uniform sampler2D texture;

varying  vec4 v_color;
varying  vec2 v_position;
varying  vec2 v_texture;
varying  vec2 v_start;
varying  float v_type;

const float factor = 2.0;
int type;

void main()
{
    type = int(v_type + 0.1);

    if (type == DATA_TYPE_LINE) {
        gl_FragColor = v_color;
    } else if (type == DATA_TYPE_DASH) {
        vec2 sub = v_position - v_start;
        float coord = length(sub.x) > length(sub.y) ? gl_FragCoord.x : gl_FragCoord.y;
        if (cos(coord / factor) > 0.0) discard;
        gl_FragColor = v_color;
    } else if (type == DATA_TYPE_DASH_DOT) {
        vec2 sub = v_position - v_start;
        float coord = length(sub.x) > length(sub.y) ? gl_FragCoord.x : gl_FragCoord.y;
        float v = cos(coord / factor * 0.5);
        if (v > 0.0 && v < 0.95) discard;
        gl_FragColor = v_color;
    } else if (type == DATA_TYPE_POINT) {
        gl_FragColor = v_color;
    } else if (type == DATA_TYPE_TRIANGLE) {
        gl_FragColor = texture2D(texture, v_texture);
    }
}