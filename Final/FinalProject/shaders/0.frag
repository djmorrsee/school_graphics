// simple toon fragment shader
// www.lighthouse3d.com

varying vec4 ecPos;
varying vec4 ambientGlobal;

uniform sampler2D tex;

void main()
{

	float dist;
	vec3 light_vec;
	
	vec4 color = ambientGlobal / 16.0 - vec4(0.1, 0.1, 0.1, 0);
	color += 1.0 / length(ecPos.xyz);
			
	color *= texture2D(tex, gl_TexCoord[0].st);
	
	gl_FragColor = color;
}
