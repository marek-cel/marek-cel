#version 110

attribute vec3 tangent;
attribute vec3 binormal;

varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;
varying mat3 TBN;

void main(void)
{
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec3 vertexPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
    vec3 lightPos = gl_LightSource[0].position.xyz;
    
    lightDir = normalize(lightPos - vertexPos);
    viewDir = normalize(-vertexPos);

    color = gl_Color.rgb;

    texCoord = gl_MultiTexCoord0.xy;

    vec3 T = normalize(gl_NormalMatrix * tangent);
    vec3 B = normalize(gl_NormalMatrix * binormal);
    vec3 N = normal;
    TBN = mat3(T, B, N);

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
