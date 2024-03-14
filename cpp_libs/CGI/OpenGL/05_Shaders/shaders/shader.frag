#version 330

in vec4 color;
in vec4 position;

out vec4 color_out;

void main(void)
{
    float amplitude = 0.5;
    float freq = 5.0;
    float phase = 0.0;

    if ( position.y < amplitude * sin(freq * position.x + phase) )
    {
        color_out = color;
    }
    else
    {
        color_out = vec4(1,1,1,1);
    }
}
