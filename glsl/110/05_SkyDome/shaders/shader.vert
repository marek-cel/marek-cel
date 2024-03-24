#version 110

varying vec3 position0;
varying vec3 position;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;

void main(void)
{
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec3 vertexPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
    vec3 lightPos = gl_LightSource[0].position.xyz;
    
    lightDir = normalize(lightPos - vertexPos);
    viewDir = normalize(-vertexPos);

    color = gl_Color.rgb;

    texCoord = gl_MultiTexCoord0.xy;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    position0 = gl_Vertex.xyz;
    position = gl_Position.xyz;
}
