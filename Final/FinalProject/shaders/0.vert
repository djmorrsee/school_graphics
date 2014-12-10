// simple toon vertex shader
// www.lighthouse3d.com

varying vec4 ecPos;
varying vec4 ambientGlobal;

void main()
{	
	int i;
	
	ecPos = gl_ModelViewMatrix * gl_Vertex;
	
	ambientGlobal = gl_LightModel.ambient + gl_FrontMaterial.ambient;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;	
	
	gl_Position = ftransform();
}
