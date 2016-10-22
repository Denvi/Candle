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
varying vec2 v_texture;

uniform sampler2D texture;

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

    // Set fragment color
    if (!isNan(v_texture.x)) {
        gl_FragColor = texture2D(texture, v_texture);
    } else {
        gl_FragColor = v_color;
    }
}
