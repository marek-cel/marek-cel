#version 330

layout(location=0) in vec3 position_in;
layout(location=3) in vec4 color_in;

out vec4 color;
out vec4 position;

uniform bool UseVertexColor = true;
uniform vec4 Color = vec4(1.0, 1.0, 0.0, 1.0);

void main()
{
    position = vec4(position_in, 1.0);
    gl_Position = position;
    color = UseVertexColor ? color_in : Color;
}