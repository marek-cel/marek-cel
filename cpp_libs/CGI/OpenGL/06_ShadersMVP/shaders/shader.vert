#version 330

layout(location=0) in vec3 position_in;
layout(location=3) in vec4 color_in;

out vec4 color;
out vec4 position;

uniform bool UseVertexColor = true;
uniform vec4 Color = vec4(1.0, 1.0, 0.0, 1.0);

const mat4 identityMat = mat4(1.0);
uniform mat4 matModel = identityMat;
uniform mat4 matView = identityMat;
uniform mat4 matProj = identityMat;
mat4 matMVP = matProj * matView * matModel;

void main()
{
    position = vec4(position_in, 1.0);
    gl_Position = matMVP * position;
    position = matModel * position;

    color = UseVertexColor ? color_in : Color;
}