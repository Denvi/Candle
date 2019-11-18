#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;

attribute vec4 a_position;
attribute vec4 a_color;
attribute vec4 a_start;

varying vec4 v_color;
varying vec2 v_position;
varying vec2 v_start;
varying vec2 v_texture;

bool isNan(float val)
{
    return (val > 65535.0);
}

void main()
{
    // Calculate interpolated vertex position & line start point
    v_position = (mv_matrix * a_position).xy;

    if (!isNan(a_start.x) && !isNan(a_start.y)) {
        v_start = (mv_matrix * a_start).xy;
        v_texture = vec2(65536.0, 0);
    } else {
        // v_start.x should be Nan to draw solid lines
        v_start = a_start.xy;

        // set texture coord
        v_texture = a_start.yz;

        // set point size
        if (isNan(a_start.y) && !isNan(a_start.z)) gl_PointSize = a_start.z;
    }

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    v_color = a_color;
}
