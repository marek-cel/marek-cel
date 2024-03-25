#version 110

varying vec3 position_orig_norm;
varying vec3 position;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;

uniform float dome_radius;

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

    position_orig_norm = gl_Vertex.xyz / dome_radius;
    position = gl_Position.xyz;
}
