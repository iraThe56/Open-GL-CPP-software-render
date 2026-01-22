#version 150

uniform sampler2D anything;

in vec2 texCoord;

out vec4 fragColor;

void main()
{
	fragColor = texture(anything, texCoord);
}