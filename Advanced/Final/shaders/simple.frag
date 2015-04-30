#version 150 core

// Atlas Texture
uniform sampler2D Atlas;

// Texture Coordinates
in vec2 tc;
out vec4 FragColor;

// VERY Simple Frag Shader
void main() {
	vec4 tex = texture2D(Atlas, tc);
	FragColor = vec4(tex);
}
