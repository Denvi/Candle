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

bool isNan(float val)
{
    return (val <= 0.0 || 0.0 <= val) ? false : true;
}

void main()
{
    // Calculate interpolated vertex position & line start point
    v_position = (mv_matrix * a_position).xy;

    if ((a_start.x != 0.0) || (a_start.y != 0.0) || (a_start.z != 0.0)) v_start = (mv_matrix * a_start).xy;
    else v_start = a_start.xy;

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Value will be automatically interpolated to fragments inside polygon faces
    v_color = a_color;
}
