#version 330 core

// Lighting Data
uniform vec3 GlobalAmbient;
uniform vec3 LightColor;

uniform float Shininess;
uniform float Strength;

in vec4 Color;
in vec3 Normal;

in vec3 LightDirection;
in vec3 HalfVector;
in float Attenuation;

// Output
layout (location = 0) out vec4 Fragcolor;

void main() {
	float diffuse = max(0.0, dot(Normal, LightDirection));
	float specular = max(0.0, dot(Normal, HalfVector));
	
	if (diffuse == 0.0)
		specular = 0.0;
	else 
		specular = pow(specular, Shininess) * Strength;
	
	
	vec3 ScatteredLight = GlobalAmbient + LightColor * diffuse * Attenuation + specular * Attenuation;
	vec3 rgb = min(Color.xyz * ScatteredLight, vec3(1.0));
	Fragcolor = min(vec4(rgb, 1), vec4(1.0));
}
