#version 110

varying vec3 position;
varying vec3 position_world;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec3 texCoord0;
varying vec3 texCoord1;

void main(void)
{
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec3 vertexPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
    vec3 lightPos = gl_LightSource[0].position.xyz;
    
    lightDir = normalize(lightPos - vertexPos);
    viewDir = normalize(-vertexPos);

    color = gl_Color.rgb;

    texCoord0 = gl_MultiTexCoord0.xyz;
    texCoord1 = gl_MultiTexCoord1.xyz;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    position = gl_Position.xyz;
    position_world = gl_Vertex.xyz;
}
