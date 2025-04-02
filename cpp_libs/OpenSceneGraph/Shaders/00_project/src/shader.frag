uniform sampler2D cTex;
uniform sampler2D nTex;
varying vec3 lightDir;

void main()
{
    vec4 base = texture2D( cTex, gl_TexCoord[0].xy );
    vec3 bump = texture2D( nTex, gl_TexCoord[0].xy ).xyz;

    bump = normalize( bump * 2.0 - 1.0 );

    float lambert = max( dot( bump, lightDir ), 0.0 );

    if ( lambert > 0.0 )
    {
        gl_FragColor = base * gl_LightSource[0].diffuse * lambert;
        gl_FragColor += gl_LightSource[0].specular * pow( lambert, 2.0 );
    }

    gl_FragColor += gl_LightSource[0].ambient;
}
