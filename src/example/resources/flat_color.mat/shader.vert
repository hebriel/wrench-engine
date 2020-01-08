#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 w_mvp;
uniform vec4 u_Color;

out vec4 o_Color;

void main()
{
	o_Color = u_Color;
	gl_Position = w_mvp * vec4(a_Position, 1.0);
}
