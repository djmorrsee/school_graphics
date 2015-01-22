// simple toon fragment shader
// www.lighthouse3d.com

varying vec4 light_pos[8];
varying vec4 light_diff[8];
varying vec3 light_hv[8];

varying vec4 ambientGlobal, ecPos;
varying vec3 normal;

uniform sampler2D tex;
void main()
{
	
	int i;
	float att, dist, NdotL, NdotHV;
	vec3 n = normalize(normal);
	
	vec3 lightDir, halfV;
	vec4 texel;
	vec4 totalLight = ambientGlobal;
	
	
	float cAtt = 2.0;
	float lAtt = 1.0;
	float qAtt = 0.66;
	
	for (i = 0; i < 8; ++i) 
	{
		lightDir = vec3(light_pos[i] - ecPos);
		NdotL = max(dot(n, normalize(lightDir)), 0.0);
		if (NdotL > 0.0)
		{
			dist = length (lightDir);
			att = 1.0 / (cAtt + lAtt * dist + qAtt * dist * dist);
		
			halfV = normalize(light_hv[i]);
			NdotHV = max(dot(n, halfV), 0.0);
		
			totalLight += att * (light_diff[i] * NdotL);	
		}
	}
	
	// Textures
	totalLight *= texture2D(tex, gl_TexCoord[0].st);
	
	gl_FragColor = totalLight;
}
