#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;

out vec2 v_texcoord;
out vec4 Position_v;
out vec4 Normal_v;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    v_texcoord = vCoordTexture;
    Position_v = vPosition;
    Normal_v = normal;
}
