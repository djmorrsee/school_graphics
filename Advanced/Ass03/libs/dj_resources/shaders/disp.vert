// Displacement shader
// djmorrsee

varying float height;
varying vec4 color;

float sin_wave(float per)
{
	return sin(per);
}

float square_wave(float per)
{
	float res;
	if (floor(sin(per)) == 0.0)
		res = 0.5;
	else
		res = -0.5;
	return res;
}

// Taken From stored.vert
vec4 phong()
{
	vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 N = normalize(gl_NormalMatrix * gl_Normal);
	vec3 LightPos = vec3(gl_LightSource[0].position);
	vec3 L = normalize(LightPos - P);
	vec3 R = reflect(-L, N);
	vec3 V = normalize(-P);
	
	float Id = max(dot(L,N), 0);
	float Is = (Id > 0.0) ? pow(max(dot(R, V), 0.0), gl_FrontMaterial.shininess) : 0.0;
	return gl_FrontMaterial.emission
		+ gl_LightModel.ambient * gl_FrontMaterial.ambient
		+ gl_FrontLightProduct[0].ambient
		+ Id*gl_FrontLightProduct[0].diffuse
		+ Is*gl_FrontLightProduct[0].specular;
}

void main()
{
	vec4 p = phong();
	gl_FrontColor = p;
	
	float h_off = length(p);
	h_off = (h_off * h_off) / 2.0 - 10.0;
	vec4 offset = vec4(0, h_off, 0, 0);

	gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + offset);
}
