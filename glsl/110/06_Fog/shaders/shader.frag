#version 110

varying vec3 position;
varying vec3 position_world;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewVec;
varying vec3 color;
varying vec2 texCoord;

uniform sampler2D texture0;

const vec3 fogColor = vec3(0.6, 0.6, 0.6);

vec3 get_phong()
{
    vec3 texelColor = vec3(texture2D(texture0, texCoord));
    vec3 N = normalize(normal); // Normal vector
    vec3 L = normalize(lightDir); // Light direction vector
    vec3 V = normalize(viewVec); // View vector

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * gl_LightSource[0].ambient.rgb * texelColor;
    vec3 diffuse = max(dot(N, L), 0.0) * gl_LightSource[0].diffuse.rgb * texelColor;

    const float shininess = 32.0; // Shininess factor
    vec3 R = reflect(-L, N); // Reflected light direction
    vec3 specular = pow(max(dot(V, R), 0.0), shininess) * gl_LightSource[0].specular.rgb;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(void)
{
    vec3 fragColor = get_phong();

    if ( position_world.z < 0.005 )
    {
        float coef = 1.0 - position_world.z / 0.005;
        coef = max(min(coef, 1.0), 0.0);
        coef *= coef;
        fragColor = mix(fragColor, fogColor, coef);
    }

    gl_FragColor = vec4(fragColor, 1.0);
}
