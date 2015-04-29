/*
 * blocks.h
 *
 *  Created on: April 28, 2015
 *      Author: djmorrsee
 */

#ifndef __BLOCKS_H
#define __BLOCKS_H

#include "../dj.h"

class block {
	int block_id;
	int x;
	int y;
	int z;
public:
	block(int id);
	block(block *b);
	float GetID();
};

#endif
