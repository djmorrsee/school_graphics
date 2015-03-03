#version 330 core

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

// Vertex Attributs 
layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec3 VertexColor;
layout(location = 2) in vec3 VertexNormal;

// Output
out vec3 FrontColor;
out vec3 Normal;
out vec4 Position;

out vec3 LightDirection;
out vec3 HalfVector;
out float Attenuation;

void main()
{
	FrontColor = VertexColor;
	Normal = normalize(NormalMatrix * VertexNormal);
	Position = ModelViewMatrix * VertexPosition;
	
	//~ LightDirection = LightPosition - vec3(VertexPosition);
	//~ float lightDistance = length(LightDirection);
	//~ 
	//~ LightDirection = LightDirection / lightDistance;
	//~ 
	//~ Attenuation = 0.5f;
	//~ 
	//~ HalfVector = normalize(LightDirection + EyePosition);
	
	gl_Position = ProjectionMatrix * ModelViewMatrix * VertexPosition;
}
