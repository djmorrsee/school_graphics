#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

layout(points) in;
layout(triangle_strip, max_vertices=9) out;

void main() {

	mat4 mvp = ModelViewMatrix;
	
	gl_Position = (gl_in[0].gl_Position + vec4(-.5, -.5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(-.5, .5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(.5, -.5, -.5, 0));
	EmitVertex();
	EndPrimitive();
	
	
	gl_Position = (gl_in[0].gl_Position + vec4(-.5, .5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(.5, .5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(.5, -.5, -.5, 0));
	EmitVertex();
	EndPrimitive();
	
	
	gl_FrontColor = vec4(1, 0, 0, 1);

	gl_Position = (gl_in[0].gl_Position + vec4(-.5, -.5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(-.5, .5, -.5, 0));
	EmitVertex();
	
	gl_Position = (gl_in[0].gl_Position + vec4(-.5, .5, .5, 0));
	EmitVertex();
	EndPrimitive();
	
}
