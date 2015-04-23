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

struct block {
	int block_id;
};

struct chunk {
	int dim;
	std::map<int, std::map<int, std::map<int, block> > > blocks;
};

chunk CreateChunk(int dim);

block GetBlock(chunk chk, int x, int y, int z);
std::vector<int> GetBlockList(chunk chk);

int BindChunkTexture(chunk chk);
#endif
