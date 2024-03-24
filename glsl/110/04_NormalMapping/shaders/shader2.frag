#version 110

varying vec3 position;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;

uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;

uniform bool blinn;
uniform bool normalMapping;

mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )
{
    // get edge vectors of the pixel triangle
    vec3 dp1 = dFdx( p );
    vec3 dp2 = dFdy( p );
    vec2 duv1 = dFdx( uv );
    vec2 duv2 = dFdy( uv );

    // solve the linear system
    vec3 dp2perp = cross( dp2, N );
    vec3 dp1perp = cross( N, dp1 );
    vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
    vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

    // construct a scale-invariant frame 
    float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
    return mat3( T * invmax, B * invmax, N );
}

vec3 get_phong()
{
    vec3 N = normalize(normal); // Normal vector
    vec3 L = normalize(lightDir); // Light direction vector
    vec3 V = normalize(viewDir); // View vector

    vec3 albedoColor = texture2D(colorMap, texCoord).rgb;
    vec3 normalColor = texture2D(normalMap, texCoord).rgb;
    float roughness = texture2D(roughnessMap, texCoord).r;

    if ( normalMapping )
    {
        vec3 normalColorNormal = normalize(normalColor * 2.0 - 1.0);
        mat3 TBN = cotangent_frame(N, position, texCoord);
        N = normalize(TBN * normalColorNormal);
    }

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * gl_LightSource[0].ambient.rgb * albedoColor;

    // diffuse
    float diffuseStrength = 0.5;
    vec3 diffuse = diffuseStrength * max(dot(N, L), 0.0) * gl_LightSource[0].diffuse.rgb * albedoColor;

    // specular
    const float shininess = 32.0; // Shininess factor
    float specStrength = (1.0 - roughness);
    
    float spec = 0.0;
    if ( blinn )
    {
        vec3 H = normalize(lightDir + viewDir); // Halway direction
        spec = pow(max(dot(N, H), 0.0), shininess);
    }
    else
    {
        vec3 R = reflect(-L, N); // Reflected light direction
        spec = pow(max(dot(V, R), 0.0), shininess);
    }
    vec3 specular = specStrength * spec * gl_LightSource[0].specular.rgb;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(void)
{
    vec3 fragColor = get_phong();

    // float gamma = 2.2;
    // fragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));

    gl_FragColor = vec4(fragColor, 1.0);
}

