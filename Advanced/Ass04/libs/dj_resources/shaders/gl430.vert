#version 330 core

// Transformation Matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

// Vertex Attributs 
layout(location = 0) in vec4 Vertex;
layout(location = 1) in vec3 Color;

// Output
out vec3 FrontColor;

void main()
{
	// Interpolate Into Fragment Shader
	FrontColor = Color;
	gl_Position = ProjectionMatrix * ModelViewMatrix * Vertex;
}
