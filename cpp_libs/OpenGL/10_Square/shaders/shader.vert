#version 330 core

layout(location=0) in vec3 position_in;
layout(location=3) in vec4 color_in;

out vec4 color;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProj;

void main()
{
    vec4 position = vec4(position_in, 1.0);
    gl_Position = (matProj * matView * matModel) * position;

    color = color_in;
}