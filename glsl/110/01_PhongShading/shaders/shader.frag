#version 110

varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewVec;
varying vec3 color;

varying vec3 lightAmbient;
varying vec3 lightDiffuse;
varying vec3 lightSpecular;

vec3 get_phong()
{
    vec3 N = normalize(normal); // Normal vector
    vec3 L = normalize(lightDir); // Light direction vector
    vec3 V = normalize(viewVec); // View vector

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightAmbient * color;
    vec3 diffuse = max(dot(N, L), 0.0) * lightDiffuse * color;

    const float shininess = 32.0; // Shininess factor
    vec3 R = reflect(-L, N); // Reflected light direction
    vec3 specular = pow(max(dot(V, R), 0.0), shininess) * lightSpecular;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(void)
{
    gl_FragColor = vec4(get_phong(), 1.0);
}
