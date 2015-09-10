#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//Dash grid (px) = factor * pi;
const float factor = 2.0;

varying vec4 v_color;
varying vec2 v_position;
varying vec2 v_start;

bool isNan(float val)
{
    return (val <= 0.0 || 0.0 <= val) ? false : true;
}

void main()
{
    // Draw dash lines
    if (length(v_start) != 0.0) {
        vec2 sub = v_position - v_start;
        float coord = length(sub.x) > length(sub.y) ? gl_FragCoord.x : gl_FragCoord.y;
        if (cos(coord / factor) > 0.0) discard;
    }

    // Set fragment color from texture
    gl_FragColor = v_color;
}
