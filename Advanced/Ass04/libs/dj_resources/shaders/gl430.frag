#version 430 core

// Input from vert
in vec3 FrontColor;
layout (location = 0) out vec4 Fragcolor;

void main() {
	Fragcolor = vec4(FrontColor, 1);
}
