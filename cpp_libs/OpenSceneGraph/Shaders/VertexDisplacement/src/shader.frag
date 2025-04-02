varying float height;
const vec4 lowerColor = vec4(0.1, 0.1, 0.1, 1.0);
const vec4 higherColor = vec4(0.2, 1.0, 0.2, 1.0);

void main()
{
    gl_FragColor = mix(lowerColor, higherColor, height);
}
