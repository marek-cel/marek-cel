#version 110

varying vec3 position0;
varying vec3 position;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;

const float radius = 5.0;
const vec3 zenithColor  = vec3(0.224, 0.439, 0.761);
const vec3 horizonColor = vec3(0.714, 0.796, 0.933);

uniform float sunElev_rad;

const float twilight_elev_rad_min = -0.17;
const float twilight_elev_rad_max =  0.17;
const float twilight_elev_rad_delta = twilight_elev_rad_max - twilight_elev_rad_min;
const float horizon_haze_elev_norm_max = 0.4;

void main(void)
{
    float elev_norm = abs(position0.z) / radius;
    vec3 fragColor = zenithColor;

    if ( elev_norm < horizon_haze_elev_norm_max )
    {
        float horizon_haze_ceof = 1.0 - elev_norm / horizon_haze_elev_norm_max;
        horizon_haze_ceof *= horizon_haze_ceof;
        fragColor = mix(fragColor, horizonColor, horizon_haze_ceof);
    }

    gl_FragColor = vec4(fragColor, 1.0);
}

