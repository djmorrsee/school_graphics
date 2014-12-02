/*
 * glob_var.c
 *
 *  Created on: Dec 1, 2014
 *      Author: djmorrsee
 */

#include "dj.h"

float vfield_of_view = 45;
float vaspect_ratio = 1;
float vclipping_plane = 10000;

// User View Rotation
float vx_persp_rot = 0;
float vy_persp_rot = 0;

float vlook_vector[3] = {0, 0, -1};

// User View Location
// This is the "origin" for gluLookAt
float vcamera_location[3] = {0, 0, 5};

void Rotate (float x, float y)
{
	vx_persp_rot += x;
	vy_persp_rot += y;

	vlook_vector[0] = Sin(vx_persp_rot);
	vlook_vector[1] = 0;
	vlook_vector[2] = -Cos(vx_persp_rot);
}

void Move(facing_t dir)
{
	switch(dir)
	{
	case left:
		vcamera_location[0] += vlook_vector[2] * move_speed;
		vcamera_location[1] += vlook_vector[1] * move_speed;
		vcamera_location[2] -= vlook_vector[0] * move_speed;
		break;
	case right:
		vcamera_location[0] -= vlook_vector[2] * move_speed;
		vcamera_location[1] += vlook_vector[1] * move_speed;
		vcamera_location[2] += vlook_vector[0] * move_speed;
		break;
	case forward:
		vcamera_location[0] += vlook_vector[0] * move_speed;
		vcamera_location[1] += vlook_vector[1] * move_speed;
		vcamera_location[2] += vlook_vector[2] * move_speed;
		break;
	case backward:
		vcamera_location[0] -= vlook_vector[0] * move_speed;
		vcamera_location[1] -= vlook_vector[1] * move_speed;
		vcamera_location[2] -= vlook_vector[2] * move_speed;
		break;
	case up:
		break;
	case down:
		break;
	}
}
