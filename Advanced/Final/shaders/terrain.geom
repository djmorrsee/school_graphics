#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVPMatrix;

// All this needs to match data in openGL
int CHUNK_DIM = 8;
int CHUNK_SQUARE = CHUNK_DIM * CHUNK_DIM;
int CHUNK_HEIGHT = 4;
uniform float Cube_IDs[256]; // 8 * 8 * 4

layout(points) in;

layout(triangle_strip, max_vertices = 36)  out;

void BuildVert(vec4 position) {
	gl_Position = position * MVPMatrix;
	EmitVertex();
}

void BuildFrontFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(0, 0, 0, 1) + offset);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();
	
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(0, scale, 0, 1) + offset);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	
	EndPrimitive();
}

void BuildBackFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(0, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	EndPrimitive();
	
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	
	EndPrimitive();

}

void BuildLeftFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(0, 0, 0, 1) + offset);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();
	
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();

}

void BuildRightFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(scale, 0, 0, 1) + offset);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
	
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();

}

void BuildTopFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(0, scale, 0, 1) + offset);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
				
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
}

void BuildBottomFace(vec4 origin, float scale) {

	vec4 thisColor = gl_FrontColor;
	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	BuildVert(vec4(0, 0, 0, 1) + offset);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	EndPrimitive();
				
	gl_FrontColor = thisColor * 0.8;
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	EndPrimitive();

}

int IndexFromXYZ(float x, float y, float z) {
	int r = int(z) * CHUNK_DIM * CHUNK_DIM + int(y) * CHUNK_DIM + int(x);
	return r;
}

vec3 XYZFromIndex(int i) {
	vec3 v;
	v.z = i / (CHUNK_DIM * CHUNK_DIM);
	v.y = (i - v.z * CHUNK_DIM * CHUNK_DIM) / (CHUNK_DIM);
	v.x = int((i - v.z * CHUNK_DIM * CHUNK_DIM) - v.y * CHUNK_DIM) % CHUNK_DIM;
	return v;
}

void main() {

	mat4 mvp = ModelViewMatrix * ProjectionMatrix;
	float scale = 0.1;
	vec4 pos = gl_in[0].gl_Position;
	vec3 index = vec3(pos.x, pos.z, pos.y);	
	
	if(Cube_IDs[IndexFromXYZ(index.x, index.y, index.z)] == 1.0) {
		vec4 draw_pos = pos.xyzw * scale; // switch y and z, and negate z
		draw_pos.y = -draw_pos.y;
		
		// Draw front face if nothing in front, or if on edge.
		//if(Cube_IDs[IndexFromXYZ(index.x, index.y + 1, index.z)] == 1.0 || index.y == CHUNK_DIM - 1) {
			gl_FrontColor = vec4(1, 1, 1, 1);
			BuildFrontFace(draw_pos, scale);
		//}

		//if(Cube_IDs[IndexFromXYZ(index.x, index.y - 1, index.z)] == 1.0 || index.y == 0) {
			gl_FrontColor = vec4(1, 1, 0, 1);
			BuildBackFace(draw_pos, scale);	
		//}
		
		//if(Cube_IDs[IndexFromXYZ(index.x - 1, index.y, index.z)] == 1.0 || int(index.x) == 0) {
			gl_FrontColor = vec4(1, 0, 0, 1);
			BuildLeftFace(draw_pos, scale);
		//}
		
		//if(Cube_IDs[IndexFromXYZ(index.x + 1, index.y, index.z)] == 1.0 || int(index.x) == CHUNK_DIM - 1) {
			gl_FrontColor = vec4(0, 0, 1, 1);
			BuildRightFace(draw_pos, scale);
		//}
		
		//if(Cube_IDs[IndexFromXYZ(index.x - 1, index.y, index.z)] == 1.0) {
			gl_FrontColor = vec4(0, 1, 1, 1);
			BuildTopFace(draw_pos, scale);
		//}
		gl_FrontColor = vec4(0, 1, 0, 1);
		BuildBottomFace(draw_pos, scale);
	}
	

	
}
