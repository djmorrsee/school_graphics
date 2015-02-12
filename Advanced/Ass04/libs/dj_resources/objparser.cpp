#include "../../dj.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>

void load_obj(const char* filename, float *buffer) 
{
	std::vector<glm::vec4> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> tcs;
	
	std::ifstream in(filename, std::fstream::in);
	if(!in) {
		printf("ERROR IN THE OBJ LOADER\n");
		exit(EXIT_FAILURE);
	}					
	std::string line;
	
	std::vector<float> data_buffer;
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
		} else if (line.substr(0, 2) == "vn") {
			std::istringstream s(line.substr(3));
			glm::vec3 vn;
			
			s >> vn.x;
			s >> vn.y;
			s >> vn.z;
			
			norms.push_back(vn);
		} else if (line.substr(0, 2) == "vt") {
			std::istringstream s(line.substr(3));
			glm::vec2 vt;
			
			s >> vt.x;
			s >> vt.y;
			
			tcs.push_back(vt);
		} else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			std::string a, b, c;
			
			s >> a;
			s >> b;
			s >> c;
			
			glm::vec4 va, vb, vc;
			glm::vec3 na, nb, nc;
			glm::vec2 ta, tb, tc;
			
			std::string del = "/";
			
			
			int vidx, tcidx, nidx;
			glm::vec4 thisVert;
			glm::vec3 thisNormal;
			glm::vec2 thisTexCoord;
			
			// First Vert
			vidx = atoi(a.substr(0, a.find(del)).c_str());
			a.erase(0, a.find(del) + del.length());
			
			tcidx = atoi(a.substr(0, a.find(del)).c_str());
			a.erase(0, a.find(del) + del.length());
			
			nidx = atoi(a.substr(0, a.find(del)).c_str());

			if (vidx > 0) {
				thisVert = verts[vidx-1];
				data_buffer.push_back(thisVert.x);
				data_buffer.push_back(thisVert.y);
				data_buffer.push_back(thisVert.z);
				data_buffer.push_back(thisVert.w);
			}
			if(tcidx > 0) {
				thisTexCoord = tcs[tcidx - 1];
				data_buffer.push_back(thisTexCoord.x);
				data_buffer.push_back(thisTexCoord.y);
			} else {
				data_buffer.push_back(-1);
				data_buffer.push_back(-1);
			}
			if (nidx > 0) {
				thisNormal = norms[nidx - 1];
				data_buffer.push_back(thisNormal.x);
				data_buffer.push_back(thisNormal.y);
				data_buffer.push_back(thisNormal.z);
			}
			
			// Second Vert
			vidx = atoi(b.substr(0, b.find(del)).c_str());
			b.erase(0, b.find(del) + del.length());
			
			tcidx = atoi(b.substr(0, b.find(del)).c_str());
			b.erase(0, b.find(del) + del.length());
			
			nidx = atoi(b.substr(0, b.find(del)).c_str());

			if (vidx > 0) {
				thisVert = verts[vidx-1];
				data_buffer.push_back(thisVert.x);
				data_buffer.push_back(thisVert.y);
				data_buffer.push_back(thisVert.z);
				data_buffer.push_back(thisVert.w);
			}
			if(tcidx > 0) {
				thisTexCoord = tcs[tcidx - 1];
				data_buffer.push_back(thisTexCoord.x);
				data_buffer.push_back(thisTexCoord.y);
			} else {
				data_buffer.push_back(-1);
				data_buffer.push_back(-1);
			} 
			if (nidx > 0) {
				thisNormal = norms[nidx - 1];
				data_buffer.push_back(thisNormal.x);
				data_buffer.push_back(thisNormal.y);
				data_buffer.push_back(thisNormal.z);
			}
			
			// Third Vert
			vidx = atoi(c.substr(0, c.find(del)).c_str());
			c.erase(0, c.find(del) + del.length());
			
			tcidx = atoi(c.substr(0, c.find(del)).c_str());
			c.erase(0, c.find(del) + del.length());
			
			nidx = atoi(c.substr(0, c.find(del)).c_str());

			if (vidx > 0) {
				thisVert = verts[vidx-1];
				data_buffer.push_back(thisVert.x);
				data_buffer.push_back(thisVert.y);
				data_buffer.push_back(thisVert.z);
				data_buffer.push_back(thisVert.w);
			}
			if(tcidx > 0) {
				thisTexCoord = tcs[tcidx - 1];
				data_buffer.push_back(thisTexCoord.x);
				data_buffer.push_back(thisTexCoord.y);
			} else {
				data_buffer.push_back(-1);
				data_buffer.push_back(-1);
			}
			if (nidx > 0) {
				thisNormal = norms[nidx - 1];
				data_buffer.push_back(thisNormal.x);
				data_buffer.push_back(thisNormal.y);
				data_buffer.push_back(thisNormal.z);
			}
		}
	}
	
	for(int i = 0; i < data_buffer.size() && i < sizeof(buffer); ++i) 
	{
		buffer[i] = data_buffer[i];
	}
}

void CreateArrayBuffers() 
{
		
}
