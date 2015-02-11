#include "../../dj.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>

void load_obj(const char* filename, std::vector<glm::vec4> &verts, 
									std::vector<glm::vec3> &norms, 
									std::vector<glm::vec3> &colors, 
									std::vector<glm::vec2> &tcs) 
{
	std::ifstream in(filename, std::fstream::in);
	if(!in) {
		printf("ERROR IN THE OBJ LOADER\n");
		exit(EXIT_FAILURE);
	}					
	std::string line;
	while (getline(in, line))
	{
		// Add Vertices
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec4 v;
			
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			
			verts.push_back(v);
		}
	}
}

void CreateArrayBuffers() 
{
		
}
