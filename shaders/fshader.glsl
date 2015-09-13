#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//Dash grid (px) = factor * pi;
const float factor = 2.0;

uniform float point_size;

varying vec4 v_color;
varying vec2 v_position;
varying vec2 v_start;

bool isNan(float val)
{
    return (val > 65535.0);
}

void main()
{
    // Draw dash lines
    if (!isNan(v_start.x)) {
        vec2 sub = v_position - v_start;
        float coord = length(sub.x) > length(sub.y) ? gl_FragCoord.x : gl_FragCoord.y;
        if (cos(coord / factor) > 0.0) discard;
    }
#ifdef GL_ES
    if (point_size > 0.0) {
        vec2 coord = gl_PointCoord.st - vec2(0.5, 0.5);
        if (length(coord) > 0.5) discard;
    }
#endif

    // Set fragment color from texture
    gl_FragColor = v_color;
}
