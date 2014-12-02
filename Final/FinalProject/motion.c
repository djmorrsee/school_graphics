#include "dj.h"
#include "motion.h"

void Rotate (float x, float y)
{
	vx_persp_rot += x;
	vy_persp_rot += y;

	float _x_rot[3] = { Sin(vx_persp_rot), 0, -Cos(vx_persp_rot) };
	float _y_rot[3] = { 0, Sin(vy_persp_rot), Cos(vy_persp_rot) };

	vlook_vector[0] = _x_rot[0] + _y_rot[0];
	vlook_vector[1] = _x_rot[1] + _y_rot[1];
	vlook_vector[2] = _x_rot[2] + _y_rot[2];
	
	norm_vert(vlook_vector);
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
