#version 110

varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewVec;
varying vec3 color;
varying vec2 texCoord;

uniform sampler2D noiseTex;
uniform float osg_FrameTime;

vec3 get_phong()
{
    vec3 N = normalize(normal); // Normal vector
    vec3 L = normalize(lightDir); // Light direction vector
    vec3 V = normalize(viewVec); // View vector

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * gl_LightSource[0].ambient.rgb * color;
    vec3 diffuse = max(dot(N, L), 0.0) * gl_LightSource[0].diffuse.rgb * color;

    const float shininess = 32.0; // Shininess factor
    vec3 R = reflect(-L, N); // Reflected light direction
    vec3 specular = pow(max(dot(V, R), 0.0), shininess) * gl_LightSource[0].specular.rgb;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(void)
{
    vec3 phong_color = get_phong();

    //float factor = osg_FrameTime * 100.0;
    float factor = 100.0;
    vec2 uv = vec2(0.4*sin(factor), 0.4*cos(factor));
    vec3 n = texture2D(noiseTex, (texCoord*3.5) + uv).rgb;

    float lum = dot(vec3(0.30, 0.59, 0.11), phong_color);
    if (lum < 0.2) phong_color *= 4.0;

    vec3 finalColor = (phong_color + (n*0.2)) * vec3(0.1, 0.95, 0.2);

    gl_FragColor = vec4(finalColor, 1.0);
}

