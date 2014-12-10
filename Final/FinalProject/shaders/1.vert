// simple toon vertex shader
// www.lighthouse3d.com

varying vec4 light_pos[8];
varying vec4 light_diff[8];
varying vec4 light_spec[8];
varying vec3 light_hv[8];

varying vec4 ambientGlobal, ecPos;
varying vec3 normal;

void main()
{	
	ecPos = gl_ModelViewMatrix * gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);

	
	int i = 0;
	for (i; i < 8; ++i)
	{
		light_pos[i] = gl_LightSource[i].position;
		light_diff[i] = gl_LightSource[i].diffuse;
		light_spec[i] = gl_LightSource[i].specular;
		light_hv[i] = gl_LightSource[i].halfVector.xyz;
	}
	
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;	
	gl_Position = ftransform();
}
