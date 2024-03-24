#version 110

varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewVec;
varying vec3 color;
varying vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

vec3 get_phong()
{
    vec3 texelColor = vec3(texture2D(texture0, texCoord));
    vec3 roughnessMap = vec3(texture2D(texture1, texCoord));
    vec3 cloudsCover = vec3(texture2D(texture2, texCoord));

    float roughness = min(roughnessMap.r + cloudsCover.r, 1.0);

    texelColor.r = min(texelColor.r + cloudsCover.r, 1.0);
    texelColor.g = min(texelColor.g + cloudsCover.g, 1.0);
    texelColor.b = min(texelColor.b + cloudsCover.b, 1.0);

    vec3 N = normalize(normal); // Normal vector
    vec3 L = normalize(lightDir); // Light direction vector
    vec3 V = normalize(viewVec); // View vector

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * gl_LightSource[0].ambient.rgb * texelColor;
    vec3 diffuse = max(dot(N, L), 0.0) * gl_LightSource[0].diffuse.rgb * texelColor;

    const float shininess = 32.0; // Shininess factor
    vec3 R = reflect(-L, N); // Reflected light direction
    vec3 specular = (1.0 - roughness) * pow(max(dot(V, R), 0.0), shininess) * gl_LightSource[0].specular.rgb;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(void)
{
    gl_FragColor = vec4(get_phong(), 1.0);
}

