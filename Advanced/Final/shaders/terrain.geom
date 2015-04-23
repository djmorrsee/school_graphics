#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVPMatrix;

layout(points) in;

layout(triangle_strip, max_vertices = 36)  out;

// Facing
// 0 - Forward
// 1 - Back
// 2 - Left
// 3 - Right
// 4 - Top
// 5 - Bottom

void BuildVert(vec4 position) {
	gl_Position = position * MVPMatrix;
	EmitVertex();
}

void BuildFace(vec4 origin, int facing, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	switch (facing) {
		case 0:
			
			BuildVert(vec4(0, 0, 0, 1) + offset);
			BuildVert(vec4(scale, 0, 0, 1) + offset);
			BuildVert(vec4(0, scale, 0, 1) + offset);
			EndPrimitive();
			
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(0, scale, 0, 1) + offset);
			BuildVert(vec4(scale, scale, 0, 1) + offset);
			BuildVert(vec4(scale, 0, 0, 1) + offset);
			
			EndPrimitive();
			
			break;
			
		case 1:
		
			BuildVert(vec4(0, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, 0, -scale, 1) + offset);
			BuildVert(vec4(0, scale, -scale, 1) + offset);
			EndPrimitive();
			
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(0, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, 0, -scale, 1) + offset);
			
			EndPrimitive();
			break;
		case 2:
			BuildVert(vec4(0, 0, 0, 1) + offset);
			BuildVert(vec4(0, 0, -scale, 1) + offset);
			BuildVert(vec4(0, scale, 0, 1) + offset);
			EndPrimitive();
			
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(0, 0, -scale, 1) + offset);
			BuildVert(vec4(0, scale, -scale, 1) + offset);
			BuildVert(vec4(0, scale, 0, 1) + offset);
			EndPrimitive();
		
			break;
		case 3:
			BuildVert(vec4(scale, 0, 0, 1) + offset);
			BuildVert(vec4(scale, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, 0, 1) + offset);
			EndPrimitive();
			
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(scale, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, 0, 1) + offset);
			EndPrimitive();
		
			break;
		case 4:
			BuildVert(vec4(0, scale, 0, 1) + offset);
			BuildVert(vec4(0, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, 0, 1) + offset);
			EndPrimitive();
						
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(0, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, -scale, 1) + offset);
			BuildVert(vec4(scale, scale, 0, 1) + offset);
			EndPrimitive();
			break;
		case 5:
			BuildVert(vec4(0, 0, 0, 1) + offset);
			BuildVert(vec4(0, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, 0, 0, 1) + offset);
			EndPrimitive();
						
			gl_FrontColor = thisColor * 0.8;
			BuildVert(vec4(0, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, 0, -scale, 1) + offset);
			BuildVert(vec4(scale, 0, 0, 1) + offset);
			EndPrimitive();

		default:
			break;
	}
}

void main() {

	mat4 mvp = ModelViewMatrix * ProjectionMatrix;
	float scale = 0.1;
	vec4 pos = gl_in[0].gl_Position * scale;
	
	gl_FrontColor = vec4(1, 1, 1, 1);
	BuildFace(pos, 0, scale);
	
	gl_FrontColor = vec4(1, 1, 0, 1);
	BuildFace(pos, 1, scale);
	
	gl_FrontColor = vec4(1, 0, 0, 1);
	BuildFace(pos, 2, scale);
	
	gl_FrontColor = vec4(0, 0, 1, 1);
	BuildFace(pos, 3, scale);
	
	gl_FrontColor = vec4(0, 1, 1, 1);
	BuildFace(pos, 4, scale);
	
	gl_FrontColor = vec4(0, 1, 0, 1);
	BuildFace(pos, 5, scale);
	
}
