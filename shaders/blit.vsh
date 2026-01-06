#version 330 core

in vec3 aPosition;
in vec2 aUV;

out vec2 texCoord;

void main() {
	gl_Position = vec4(aPosition.xy, 0.0, 1.0);
	texCoord = aUV;
}