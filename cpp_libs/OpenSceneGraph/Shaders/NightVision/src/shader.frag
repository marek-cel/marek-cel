uniform sampler2D sceneTex;
uniform sampler2D noiseTex;
uniform float osg_FrameTime;

void main()
{
   float factor = osg_FrameTime * 100.0;
   vec2 uv = vec2(0.4*sin(factor), 0.4*cos(factor));
   vec3 n = texture2D(noiseTex, (gl_TexCoord[0].st*3.5) + uv).rgb;

   vec3 c = texture2D(sceneTex, gl_TexCoord[0].st + (n.xy*0.005)).rgb;
   float lum = dot(vec3(0.30, 0.59, 0.11), c);
   if (lum < 0.2) c *= 4.0;

   vec3 finalColor = (c + (n*0.2)) * vec3(0.1, 0.95, 0.2);
   gl_FragColor = vec4(finalColor, 1.0);
}
