/*
 * lighting.h
 *
 *  Created on: Dec 4, 2014
 *      Author: djmorrsee
 */

#ifndef LIGHTING_H_
#define LIGHTING_H_

void set_light(int num, float x, float y, float z, float r, float g, float b);
void draw_light(int num);

void AdjustLighting(int up);

#endif /* LIGHTING_H_ */
