#version 110

varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewVec;
varying vec3 color;
varying vec2 texCoord;

void main(void)
{
    normal = normalize(gl_NormalMatrix * gl_Normal);

    vec3 vertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 lightPos = gl_LightSource[0].position.xyz;
    
    lightDir = normalize(lightPos - vertexPos);
    viewVec = normalize(-vertexPos);

    color = gl_Color.rgb;

    texCoord = gl_MultiTexCoord0.xy;

    gl_Position = ftransform();
}
