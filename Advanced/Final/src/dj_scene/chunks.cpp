#include "../dj.h"
#include "chunks.h"
#include <map>
#include <vector>

chunk::chunk() {
	dim = 0;
	height = 0;
	blocks = std::vector<block>();
}

chunk::chunk(int d, int h) {
	dim = d;
	height = h;
	
	blocks = std::vector<block>();

	for(int x = 0; x < dim; ++x) {
		for(int y = 0; y < dim; ++y) {
			for(int z = 0; z < height; ++z) {
				block b = block(rand() % 2);
				blocks.push_back(b);
			}
		}
	}
}

std::vector<float> chunk::flatPositionMap(){ // ((x,y,z),(x,y,z)) but flat...
	std::vector<float> list;
	int d_off = dim / 2.0f;
	int h_off = height / 2.0f;
	for (int i = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			for (int k = 0; k < height; ++k) {
				list.push_back(i);
				list.push_back(k);
				list.push_back(j); // Reversed x and y
			}
		}
	}
	
	return list;
}

std::vector<float> chunk::flatIDMap() {
	std::vector<float> list;
	
	for (int i = 0; i < blocks.size(); ++i) {
		list.push_back(blocks[i].GetID());
	}
	
	return list;
}

//~ 
//~ block chunk::GetBlock(int x, int y, int z) {
	//~ block* b = blocks[x][z][y];
	//~ return block(b);
//~ }
