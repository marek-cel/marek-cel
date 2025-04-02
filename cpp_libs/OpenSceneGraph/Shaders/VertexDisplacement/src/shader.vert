uniform sampler2D defaultTex;
varying float height;

void main()
{
    vec2 uv = gl_MultiTexCoord0.xy;
    vec4 color = texture2D(defaultTex, uv);
    height = 0.3*color.x + 0.59*color.y + 0.11*color.z;

    vec4 pos = gl_Vertex;
    pos.z = pos.z + 100.0*height;
    gl_Position = gl_ModelViewProjectionMatrix * pos;
}
