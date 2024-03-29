#version 110

varying float dist;
varying vec3 color;

void main(void)
{
    vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    dist = length(vertexPos);

    color = gl_Color.rgb;

    gl_Position = ftransform();
}
