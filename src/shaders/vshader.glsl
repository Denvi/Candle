#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform float point_size;

attribute vec4 a_position;
attribute vec4 a_color;
attribute vec4 a_start;

varying vec4 v_color;
varying vec2 v_position;
varying vec2 v_start;

bool isNan(float val)
{
    return (val > 65535.0);
}

void main()
{
    // Calculate interpolated vertex position & line start point
    v_position = (mv_matrix * a_position).xy;

    if (!isNan(a_start.x)) v_start = (mv_matrix * a_start).xy;
    else v_start = a_start.xy;

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Value will be automatically interpolated to fragments inside polygon faces
    v_color = a_color;

    // Set point size
    gl_PointSize = point_size;
}
