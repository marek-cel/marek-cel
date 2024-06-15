#version 330 core

in vec3 FragColor;
in vec3 FragPos;
in vec3 FragNorm;
in vec2 FragTexCoord;

out vec4 color_out;

uniform vec3 lightColor = vec3(1,1,1);
uniform vec3 lightPos = vec3(5,2,1);

uniform vec3 cameraPos = vec3(0,0,1);

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shinessVal;

uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

vec3 get_ambient(vec3 color)
{
    float ambientStrength = 0.1;
    return ambientStrength * lightColor * ambientColor;
}

vec3 get_diffuse(vec3 pos, vec3 norm, vec3 color)
{
    vec3 n = normalize(norm);
    vec3 lightDir = normalize(lightPos - pos);
    float diff = max(dot(n, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * diffuseColor;
    return diffuse;
}

vec3 get_specular(vec3 pos, vec3 norm, float coef)
{
    vec3 n = normalize(norm);
    vec3 viewDir = normalize(cameraPos - pos);
    vec3 lightDir = normalize(lightPos - pos);
    vec3 reflectDir = reflect(-lightDir, n);

    float specularStrength = 0.5*coef;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinessVal);
    vec3 specular = specularStrength * spec * lightColor * specularColor;
    return specular;
}

vec3 get_phong(vec3 pos, vec3 norm, vec2 texCoord, vec3 color)
{
    vec4 texel0 = texture2D(texSampler0, texCoord);
    vec4 texel1 = texture2D(texSampler1, texCoord);
    //texel0 = texel0 * texel1.x;
    //texel0 = texel1;
    vec3 result = get_ambient(color)*vec3(texel0)
                + get_diffuse(pos, norm, color)*vec3(texel0)
                + get_specular(pos, norm, texel1.x);
    return result;
}

void main(void)
{
    color_out = vec4(get_phong(FragPos, FragNorm, FragTexCoord, FragColor), 1.0);
}
