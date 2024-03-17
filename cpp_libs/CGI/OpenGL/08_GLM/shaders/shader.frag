#version 330 core

in vec4 color;
in vec4 position;

uniform bool Wave = true;
uniform vec4 WaveColor = vec4(0.0, 1.0, 1.0, 1.0);

out vec4 color_out;

void main(void)
{
    float amplitude = 0.25;
    float freq = 10.0;
    float phase = 0.0;

    if ( Wave && (position.y < amplitude * sin(freq * position.x + phase)) )
    {
        color_out = color;
    }
    else
    {
        color_out = WaveColor;
    }
}
