// simple toon fragment shader
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
	
	int i;
	float att, dist, NdotL, NdotHV;
	vec3 n = normalize(normal);
	
	vec3 lightDir, halfV;
	
	vec4 totalLight = ambientGlobal;
	
	// Light 0
	lightDir = vec3(lPos0 - ecPos);	
	NdotL = max(dot(n, normalize(lightDir)), 0.0);
	if(NdotL > 0.0)
	{
		dist = length(lightDir);
		att = 1.0 / (cAtt + lAtt * dist + qAtt * dist * dist);
		
		totalLight += att * (diff0 * NdotL + amb0);
		
		halfV = normalize(hv0);
		NdotHV = max(dot(n, halfV), 0.0);
		totalLight += att * vec4(1, 1, 1, 1); // This should be amb0 // 
	}
	
	// Light 1
	lightDir = vec3(lPos1 - ecPos);	
	NdotL = max(dot(n, normalize(lightDir)), 0.0);
	if(NdotL > 0.0)
	{
		dist = length(lightDir);
		att = 1.0 / (cAtt + lAtt * dist + qAtt * dist * dist);
		
		totalLight += att * (diff1 * NdotL + amb1);
		
		halfV = normalize(hv1);
		NdotHV = max(dot(n, halfV), 0.0);
		totalLight += att * vec4(1, 1, 1, 1);
	}
	
	gl_FragColor = totalLight;
}
