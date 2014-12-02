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

float* get_look_position()
{
	float f[3] = { vcamera_location[0] + vlook_vector[0], vcamera_location[1] + vlook_vector[1], vcamera_location[2] + vlook_vector[2] };
	return f;
}

