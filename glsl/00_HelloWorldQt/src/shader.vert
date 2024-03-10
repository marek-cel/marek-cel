#version 330 core

//attribute vec4 vPosition;
in vec3 vPosition;

void main(void)
{
    //gl_Position = vPosition;
    gl_Position = vec4(vPosition, 1.0);
}
