#version 330 core

// Lighting Data
uniform vec3 GlobalAmbient;
uniform vec3 LightColor;

uniform float Shininess;
uniform float Strength;

uniform vec3 LightPosition;
uniform vec3 EyePosition;

in vec4 FrontColor;
in vec3 Normal;
in vec4 Position;

// Output
layout (location = 0) out vec4 Fragcolor;

void main() {
	vec3 lightDirection = LightPosition - vec3(Position);
	float lightDistance = length(lightDirection);
	lightDirection = lightDirection / lightDistance;
	
	float attenuation = 1.0 / (1 + 0.5 * lightDistance + 0.5 * lightDistance * lightDistance);
	vec3 halfVector = normalize(lightDirection + EyePosition);

	float diffuse = max(0.0, dot(Normal, lightDirection));
	float specular = max(0.0, dot(Normal, halfVector));
	
	if (diffuse == 0.0)
		specular = 0.0;
	else 
		specular = pow(specular, 1) * 1;
	
	vec3 scatteredLight = GlobalAmbient + vec3(1, 1, 1) * diffuse * attenuation;
	vec3 reflectedLight = vec3(1, 1, 1) * specular * attenuation;
	vec3 rgb = min(FrontColor.xyz * scatteredLight + reflectedLight, vec3(1.0));
	
	Fragcolor = min(vec4(rgb, 1), vec4(1.0));
}
