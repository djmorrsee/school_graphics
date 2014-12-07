// simple toon vertex shader
// www.lighthouse3d.com

varying vec4 lPos0, lPos1, lPos2, lPos3, lPos4, lPos5, lPos6, lPos7;
varying vec4 diff0, diff1, diff2, diff3, diff4, diff5, diff6, diff7;
varying vec4 amb0, amb1, amb2, amb3, amb4, amb5, amb6, amb7;
varying vec3 hv0, hv1, hv2, hv3, hv4, hv5, hv6, hv7, hv8;

varying vec4 ambientGlobal, ecPos;
varying float cAtt, lAtt, qAtt;
varying vec3 normal;

void main()
{	
	ecPos = gl_ModelViewMatrix * gl_Vertex;
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	cAtt = 2.0;
	lAtt = 1.0;
	qAtt = 0.5;
	
	lPos0 = gl_LightSource[0].position;
	lPos1 = gl_LightSource[1].position;
	lPos2 = gl_LightSource[2].position;
	lPos3 = gl_LightSource[3].position;
	lPos4 = gl_LightSource[4].position;
	lPos5 = gl_LightSource[5].position;
	lPos6 = gl_LightSource[6].position;
	lPos7 = gl_LightSource[7].position;
	
	hv0 = gl_LightSource[0].halfVector.xyz;
	hv1 = gl_LightSource[1].halfVector.xyz;
	hv2 = gl_LightSource[2].halfVector.xyz;
	hv3 = gl_LightSource[3].halfVector.xyz;
	hv4 = gl_LightSource[4].halfVector.xyz;
	hv5 = gl_LightSource[5].halfVector.xyz;
	hv6 = gl_LightSource[6].halfVector.xyz;
	hv7 = gl_LightSource[7].halfVector.xyz;
	
	diff0 = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	diff1 = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
	diff2 = gl_FrontMaterial.diffuse * gl_LightSource[2].diffuse;
	diff3 = gl_FrontMaterial.diffuse * gl_LightSource[3].diffuse;
	diff4 = gl_FrontMaterial.diffuse * gl_LightSource[4].diffuse;
	diff5 = gl_FrontMaterial.diffuse * gl_LightSource[5].diffuse;
	diff6 = gl_FrontMaterial.diffuse * gl_LightSource[6].diffuse;
	diff7 = gl_FrontMaterial.diffuse * gl_LightSource[7].diffuse;
	
	amb0 = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	amb1 = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;
	amb2 = gl_FrontMaterial.ambient * gl_LightSource[2].ambient;
	amb3 = gl_FrontMaterial.ambient * gl_LightSource[3].ambient;
	amb4 = gl_FrontMaterial.ambient * gl_LightSource[4].ambient;
	amb5 = gl_FrontMaterial.ambient * gl_LightSource[5].ambient;
	amb6 = gl_FrontMaterial.ambient * gl_LightSource[6].ambient;
	amb7 = gl_FrontMaterial.ambient * gl_LightSource[7].ambient;
	
	ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;
		
	gl_Position = ftransform();
}
