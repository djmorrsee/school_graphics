#include "../dj.h"
#include "chunks.h"

chunk CreateChunk(int dim) {
	// Hard Coded Chunk Gen
	if (dim != 3) {
		exit(1);
	}
	chunk chk;
	chk.dim = dim;
	float vals[] = {
		1, 0, 1,
		0, 1, 0,
		1, 0, 1,
		
		0, 0, 0,
		0, 1, 0,
		0, 0, 0,
		
		1, 0, 1,
		0, 1, 0,
		1, 0, 1,
	};
	std::map<int, std::map<int, std::map<int, block> > > blks;
	for (int i = 0; i < dim; ++i) {
		
		std::map<int, std::map<int, block> > jb;
		for (int j = 0; j < dim; ++j) {
			std::map<int, block> kb;
			for (int k = 0; k < dim; ++k) {
				block blk;
				blk.block_id = vals[k + dim * j + dim * dim * i];
				
				kb[k] = blk;
			}
			jb[j] = kb;
		}
		blks[i] = jb;
	}
	chk.blocks = blks;
	return chk;
}

block GetBlock(chunk chk, int x, int y, int z) {
	return chk.blocks[x][y][z];
}

std::vector<int> GetBlockList(chunk chk) {
	int d = chk.dim;
	std::vector<int> list;
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < d; ++j) {
			for (int k = 0; k < d; ++k) {
				list.push_back(chk.blocks[i][j][k].block_id);
			}
		}
	}
	
	return list;
}

int BindChunkTexture(chunk chk) {
	unsigned int tex;
	glGenTextures(1, &tex);
	
	glBindTexture(GL_TEXTURE_1D, tex);
	
	int vals [] = {
		1, 1, 1
	};
	
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RED, chk.dim * chk.dim * chk.dim, 0, GL_RED,GL_INT, &vals);
	if(glGetError()) Fatal("Error Sending Texture");
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	return tex;
}
