#version 330 core

in vec4 color;
in vec4 position;

out vec4 color_out;

void main(void)
{
    color_out = color;
}
