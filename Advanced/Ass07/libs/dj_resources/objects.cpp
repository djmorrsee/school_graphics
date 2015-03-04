/*
 * objects.cpp
 * 
 * Handles various routes to generating object buffers
 * 
 */

#include "../../dj.h"
#include "objects.h"

// Hard coded monkey
#include "models/new_monkey.h"

dj_object load_object(std::string filename) {
	dj_object new_obj;
	
	glGenBuffers(1, &new_obj.pos_buffer);
	glGenBuffers(1, &new_obj.rgb_buffer);
	glGenBuffers(1, &new_obj.tc_buffer);
	glGenBuffers(1, &new_obj.norm_buffer);
	
	return new_obj;
}


dj_object create_object_from_parsed() { 
	dj_object new_obj;
		
	// Not Hard Coded
	glGenBuffers(1, &new_obj.pos_buffer);
	glGenBuffers(1, &new_obj.rgb_buffer);
	glGenBuffers(1, &new_obj.tc_buffer);
	glGenBuffers(1, &new_obj.norm_buffer);
	
	// XYZW Buffer Data
	glBindBuffer(GL_ARRAY_BUFFER, new_obj.pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_monkey_xyz), new_monkey_xyz, GL_STATIC_DRAW);
	
	// RGB Buffer Data
	glBindBuffer(GL_ARRAY_BUFFER, new_obj.rgb_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_monkey_rgb), new_monkey_rgb, GL_STATIC_DRAW);
	
	// TC Buffer Data
	glBindBuffer(GL_ARRAY_BUFFER, new_obj.tc_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_monkey_tc), new_monkey_tc, GL_STATIC_DRAW);
	
	// Bind Texture
	new_obj.texture_id = LoadTexBMP("libs/dj_resources/textures/NewMonkeyTex.bmp");
	
	// NORM Buffer Data
	glBindBuffer(GL_ARRAY_BUFFER, new_obj.norm_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(new_monkey_norm), new_monkey_norm, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return new_obj;
}
