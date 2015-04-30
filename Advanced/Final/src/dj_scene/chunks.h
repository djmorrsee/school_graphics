/*
 * chunks.h
 *
 *  Created on: April 22, 2015
 *      Author: djmorrsee
 */

#ifndef __CHUNKS_H
#define __CHUNKS_H

#include "../dj.h"
#include <map>
#include <vector>
#include <string>

void LoadChunk();

class chunk {
	int dim;
	int height;
	std::vector<block> blocks;

public:
	chunk(int d, int h);
	chunk();
	std::vector<float> flatPositionMap(); // ((x,y,z),(x,y,z)) but flat...
	std::vector<float> flatIDMap();
};

#endif
