attribute vec3 tangent;
attribute vec3 binormal;
varying vec3 lightDir;

void main()
{
    vec3 normal = normalize( gl_NormalMatrix * gl_Normal );
    mat3 rotation = mat3( tangent, binormal, normal );
    vec4 vertexInEye = gl_ModelViewMatrix * gl_Vertex;

    lightDir = vec3( gl_LightSource[0].position.xyz - vertexInEye.xyz );
    lightDir = normalize( rotation * normalize( lightDir ) );
    gl_Position = ftransform();
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
