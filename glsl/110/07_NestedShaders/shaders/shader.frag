#version 110

varying float dist;
varying vec3 color;

void main(void)
{
    vec3 black = vec3(0,0,0);
    vec3 fragColor = color;

    float dist_min = 20.0;
    if ( dist > dist_min )
    {
        float coef = (dist - dist_min) / dist_min;
        coef = max(min(coef, 1.0), 0.0);
        fragColor = mix(fragColor, black, coef);
    }

    gl_FragColor = vec4(fragColor, 1.0);
}

