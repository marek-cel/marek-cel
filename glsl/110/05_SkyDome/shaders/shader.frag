#version 110

varying vec3 position_orig_norm;
varying vec3 position;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;
varying vec3 color;
varying vec2 texCoord;

const float radius = 5.0;

uniform float sun_face_radius_norm;
uniform float sun_glare_radius_norm;
uniform vec3 sun_pos_norm;
uniform vec3 color_sky_zenith;
uniform vec3 color_sky_horizon;
uniform vec3 color_sun;
uniform float sunset_coef;

const float horizon_haze_elev_norm_max = 0.4;

void main(void)
{
    float elev_norm = abs(position_orig_norm.z);
    vec3 fragColor = color_sky_zenith;
    float distFromSunNorm = length(sun_pos_norm - position_orig_norm);
    vec3 sunPosNormXY = normalize(vec3(sun_pos_norm.xy, 0.0));
    vec3 fragPosNormXY = normalize(vec3(position_orig_norm.xy, 0.0));
    float distFromSunNormXY = length(sunPosNormXY - fragPosNormXY);

    float horizon_haze_elev_max = (1.0 + 0.5 * sunset_coef) * horizon_haze_elev_norm_max;
    if ( elev_norm < horizon_haze_elev_max )
    {
        float horizon_haze_ceof = 1.0 - elev_norm / horizon_haze_elev_max;
        if ( sunset_coef > 0.0 )
        {
            float coef = min(1.0, sunset_coef * distFromSunNormXY / 2.5);
            horizon_haze_ceof *= (1.0 - coef);
        }
        horizon_haze_ceof *= horizon_haze_ceof;
        vec3 horizonColor = mix(fragColor, color_sky_horizon, horizon_haze_ceof);
        fragColor = horizonColor;
    }

    float sun_glare_dist_max = (1.0 - 0.5 * sunset_coef) * sun_glare_radius_norm;
    if ( distFromSunNorm < sun_glare_dist_max )
    {
        float coef = distFromSunNorm / sun_glare_dist_max;
        vec3 color = mix(fragColor, color_sun, 0.2); 
        fragColor = mix(fragColor, color, 1.0 - coef);
    }

    if ( distFromSunNorm < sun_face_radius_norm )
    {
        float sun_face_radius_norm_99 = 0.99 * sun_face_radius_norm;
        if ( distFromSunNorm <  sun_face_radius_norm_99 )
        {
            fragColor = color_sun;
        }
        else
        {
            float coef = (distFromSunNorm - sun_face_radius_norm_99 ) / (0.01 * sun_face_radius_norm);
            fragColor = mix(fragColor, color_sun, 1.0 - coef);
        }
    }

    gl_FragColor = vec4(fragColor, 1.0);
}

