#version 330 core

layout(location=0) in vec3 position_in;
layout(location=1) in vec3 normal_in;
layout(location=3) in vec4 color_in;

out vec3 FragColor;
out vec3 FragPos;
out vec3 FragNorm;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProj;

void main()
{
    vec4 position = vec4(position_in, 1.0);
    gl_Position = (matProj * matView * matModel) * position;

    FragPos   = mat3(matModel) * position_in;
    FragNorm  = mat3(matModel) * normal_in;
    FragColor = vec3(color_in);
}
