// in == attribute in a vert shader, varying in frag
// out == varying in a vert shader
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

uniform vec3 LightPosition;

attribute vec4 XYZW;
attribute vec3 RGB;
attribute vec3 NORM;
attribute vec2 TEX;

// Output
varying vec3 color;
varying vec3 lighting;
varying vec2 texture_coord;

void main()
{
	color = RGB;
	texture_coord = TEX;
	
	vec3 ambient = vec3(0.2);
	vec3 dirLightRGB = vec3(0.5, 0.5, 0.5);
	
	color = RGB;
		
	gl_FrontColor = vec4(color, 1.0);
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(XYZW.xyz, 1.0);
}
