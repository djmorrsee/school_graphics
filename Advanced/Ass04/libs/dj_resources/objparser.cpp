#include "../../dj.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>

// 12 floats wide
// Num Elements Long
// Total Bytes = 12 * NE * sizeof(float)

std::vector<float> ParseVertLine(std::string line) {
		std::vector<float> xyz;
		std::istringstream s(line.substr(2));
		s >> xyz[0];
		s >> xyz[1];
		s >> xyz[2];
		return xyz;
}

std::vector<float> ParseNormalLine(std::string line) {
		std::vector<float> xyz;
		std::istringstream s(line.substr(3));
		s >> xyz[0];
		s >> xyz[1];
		s >> xyz[2];
		return xyz;
}

std::vector<float> ParseTCLine(std::string line) {
	std::vector<float> xy;
	std::istringstream s(line.substr(2));
	s >> xy[0];
	s >> xy[1];
	return xy;
}


void load_obj(const char* filename, float *buffer) 
{
	std::vector<float> data_vals;

	std::vector<std::vector<float> > verts;
	std::vector<std::vector<float> > norms;
	std::vector<std::vector<float> > tcs;
	
	
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
			std::vector<float> v = ParseVertLine(line);
			verts.push_back(v);
		} else if (line.substr(0, 2) == "vn") {
			std::vector<float> vn = ParseNormalLine(line);
			norms.push_back(vn);
		} else if (line.substr(0, 2) == "vt") {
			std::vector<float> vt = ParseTCLine(line);
			tcs.push_back(vt);
		} else if (line.substr(0, 2) == "f ") {
	
			std::istringstream s(line.substr(2));
			std::string a, b, c;
			
			s >> a;
			s >> b;
			s >> c;
			
			std::string del = "/";
			
			
			int vidx, tcidx, nidx;
			
			// First Vert
			vidx = atoi(a.substr(0, a.find(del)).c_str());
			a.erase(0, a.find(del) + del.length());
			
			tcidx = atoi(a.substr(0, a.find(del)).c_str());
			a.erase(0, a.find(del) + del.length());
			
			nidx = atoi(a.substr(0, a.find(del)).c_str());
			
			data_vals.push_back(verts.at(vidx-1)[0]);
			data_vals.push_back(verts.at(vidx-1)[1]);
			data_vals.push_back(verts.at(vidx-1)[2]);
			data_vals.push_back(verts.at(vidx-1)[3]);
			
			data_vals.push_back(norms.at(nidx-1)[0]);
			data_vals.push_back(norms.at(nidx-1)[1]);
			data_vals.push_back(norms.at(nidx-1)[2]);
			
			data_vals.push_back(1.0f);
			data_vals.push_back(1.0f);
			data_vals.push_back(1.0f);
			
			data_vals.push_back(tcs.at(tcidx-1)[1]);
			data_vals.push_back(tcs.at(tcidx-1)[2]);
			data_vals.push_back(tcs.at(tcidx-1)[3]);
			
		}
	}
	
	for(int i = 0; i < data_vals.size(); ++i) 
	{
		//printf("%.2f", data_vals[i]);
	}
}

void CreateArrayBuffers() 
{
		
}
