uniform sampler2D defaultTex;
uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D normalTex;
varying vec4 projCoords;
varying vec3 lightDir, eyeDir;
varying vec2 flowCoords, rippleCoords;

void main()
{
   vec2 rippleEffect = 0.02 * texture2D(refraction, rippleCoords * 0.1).xy;
   vec4 N = texture2D(normalTex, flowCoords + rippleEffect);
   N = N * 2.0 - vec4(1.0);
   N.a = 1.0; N = normalize(N);

   vec3 refVec = normalize(reflect(-lightDir, vec3(N) * 0.6));
   float refAngle = clamp(dot(eyeDir, refVec), 0.0, 1.0);
   vec4 specular = vec4(pow(refAngle, 40.0));

   vec2 dist = texture2D(refraction, flowCoords + rippleEffect).xy;
   dist = (dist * 2.0 - vec2(1.0)) * 0.1;
   vec2 uv = projCoords.xy / projCoords.w;
   uv = clamp((uv + 1.0) * 0.5 + dist, 0.0, 1.0);

   vec4 base = texture2D(defaultTex, uv);
   vec4 refl = texture2D(reflection, uv);
   gl_FragColor = mix(base, refl + specular, 0.6);
}
