#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 o_Color;

void main()
{
    o_Color = a_Color;
    gl_Position = vec4(a_Position, 1.0);
}
