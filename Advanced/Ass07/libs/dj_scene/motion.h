/*
 * motion.h
 *
 *  Created on: March 2nd, 2015
 *      Author: djmorrsee
 */

#include "../../dj.h"

typedef enum { left=0, right, forward, backward, up, down } facing_t;

// Abstract Motion Functions
// Alter scene based movement in these functions
void Rotate(float x, float y);
void Move(facing_t dir);
