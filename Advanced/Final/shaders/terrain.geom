#version 150 compatibility
#extension GL_EXT_geometry_shader4 : enable

// Matrices
uniform mat4 MVPMatrix;

// All this needs to match data in openGL
int CHUNK_DIM = 8;
int CHUNK_HEIGHT = 4;

// The array of cube ids (determines textures and helps with culling)
uniform float Cube_IDs[256]; // 8 * 8 * 8

// Geo Shader Data
layout(points) in;
layout(triangle_strip, max_vertices = 36)  out;

// Lerp Texture Coordinates to Frag
out vec2 tc;

// Helper Method 
void BuildVert(vec4 position) {
	gl_Position = position * MVPMatrix;
	EmitVertex();
}

/*

Build*Face draws a face in the indicated position, centered around origin.
Texture coordinates are generated for the face based on the texture ID (could abstract this out)

*/
void BuildFrontFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;
	
	tc = vec2(tx1, ty1);
	BuildVert(vec4(0, 0, 0, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	
	tc = vec2(tx2, ty2);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	
	EndPrimitive();
}

void BuildBackFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);
	
	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;
	
	tc = vec2(tx1, ty1);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	EndPrimitive();
		
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	
	tc = vec2(tx2, ty2);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	
	EndPrimitive();

}

void BuildLeftFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;
	
	tc = vec2(tx1, ty1);
	BuildVert(vec4(0, 0, 0, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();
		
	tc = vec2(tx2, ty1);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	
	tc = vec2(tx2, ty2);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, 0, 1) + offset);
	EndPrimitive();

}

void BuildRightFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);
	
	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;

	tc = vec2(tx1, ty1);
	BuildVert(vec4(scale, 0, 0, 1) + offset);

	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);

	tc = vec2(tx1, ty2);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);

	tc = vec2(tx2, ty2);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);

	tc = vec2(tx1, ty2);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();

}

void BuildTopFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;
	
	tc = vec2(tx1, ty1);
	BuildVert(vec4(0, scale, 0, 1) + offset);

	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, -scale, 1) + offset);

	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, scale, -scale, 1) + offset);
	
	tc = vec2(tx2, ty2);
	BuildVert(vec4(scale, scale, -scale, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, scale, 0, 1) + offset);
	EndPrimitive();
}

void BuildBottomFace(vec4 origin, float scale, int id) {

	vec4 offset = origin + vec4(-scale / 2.0, -scale / 2.0, scale / 2.0, 0);

	float tx1 = .25*(id);
	float tx2 = tx1 + .25;
	float ty1 = 1.0-.25;
	float ty2 = 1.0;

	tc = vec2(tx1, ty1);
	BuildVert(vec4(0, 0, 0, 1) + offset);
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	EndPrimitive();
				
	
	tc = vec2(tx1, ty2);
	BuildVert(vec4(0, 0, -scale, 1) + offset);
	
	tc = vec2(tx2, ty2);
	BuildVert(vec4(scale, 0, -scale, 1) + offset);
	
	tc = vec2(tx2, ty1);
	BuildVert(vec4(scale, 0, 0, 1) + offset);
	EndPrimitive();
}

int IndexFromXYZ(float x, float y, float z) {
	int r = int(z) * CHUNK_DIM * CHUNK_DIM + int(y) * CHUNK_DIM + int(x);
	return r;
}

void main() {
	float scale = 0.15;
	vec4 pos = gl_in[0].gl_Position;
	
	vec3 index = vec3(pos.x, pos.z, pos.y);	
	int this_id = int(Cube_IDs[IndexFromXYZ(index.x, index.y, index.z)]);
	
	if(this_id != 0) {
		vec4 draw_pos = (pos.xyzw - vec4(CHUNK_DIM / 2.0 - 1, CHUNK_HEIGHT / 2.0 , CHUNK_DIM / 2.0, 0)) * scale; // switch y and z, and negate z
		draw_pos.y = -draw_pos.y;
		
		// Draw front face if nothing in front, or if on edge.
		if(Cube_IDs[IndexFromXYZ(index.x, index.y + 1, index.z)] == 0.0 || index.y == CHUNK_DIM - 1) {
			BuildFrontFace(draw_pos, scale, this_id);
		}

		if(Cube_IDs[IndexFromXYZ(index.x, index.y - 1, index.z)] == 0.0 || index.y == 0) {
			BuildBackFace(draw_pos, scale, this_id);	
		}
		
		if(Cube_IDs[IndexFromXYZ(index.x - 1, index.y, index.z)] == 0.0 || int(index.x) == 0) {
			BuildLeftFace(draw_pos, scale, this_id);
		}
		
		if(Cube_IDs[IndexFromXYZ(index.x + 1, index.y, index.z)] == 0.0 || int(index.x) == CHUNK_DIM - 1) {
			BuildRightFace(draw_pos, scale, this_id);
		}
		
		if(Cube_IDs[IndexFromXYZ(index.x, index.y, index.z - 1)] == 0.0 || int(index.z) == 0) {
			BuildTopFace(draw_pos, scale, this_id);
		}
		if(Cube_IDs[IndexFromXYZ(index.x, index.y, index.z + 1)] == 0.0 || int(index.z) == CHUNK_HEIGHT - 1) {
			BuildBottomFace(draw_pos, scale, this_id);
		}
	}
}
