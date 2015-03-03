/*
 * lighting.h
 *
 *  Created on: March 2nd, 2015
 *      Author: djmorrsee
 */

#include "../../dj.h"

struct dj_light {
		bool isEnabled;
		bool isLocal;
		
		// Stuff I want
		float color[3];
		float position[3];
		
		// Stuff for shaders
		float halfVector[3];
};
