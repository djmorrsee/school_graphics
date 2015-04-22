#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

layout(points) in;

layout(triangle_strip, max_vertices = 9) out;

void main() {

	mat4 mvp = ModelViewMatrix * ProjectionMatrix;
	
	gl_FrontColor = vec4(0, 0.8, 0, 1);
	gl_Position = vec4(0, 0, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(.1, 0, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(0, .1, 0, 1) * mvp;
	EmitVertex();
	EndPrimitive();


	gl_FrontColor = vec4(0, .6, 0, 1);
	gl_Position = vec4(0, .1, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(.1, .1, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(.1, 0, 0, 1) * mvp;
	EmitVertex();
	EndPrimitive();
	
	
	gl_FrontColor = vec4(.8, 0, 0, 1);
	gl_Position = vec4(0, 0, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(0, .1, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(0, 0, .1, 1) * mvp;
	EmitVertex();
	EndPrimitive();


	gl_FrontColor = vec4(.6, 0, 0, 1);
	gl_Position = vec4(0, 0, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(0, .1, 0, 1) * mvp;
	EmitVertex();
	
	gl_Position = vec4(0, 0, .1, 1) * mvp;
	EmitVertex();
	EndPrimitive();
	
	
}
