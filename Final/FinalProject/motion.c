#include "dj.h"
#include "motion.h"

void Refresh ()
{
	vector3 rot = { .x = Cos(v_x_persp_rot) * Cos(v_y_persp_rot), Sin(v_y_persp_rot), Sin(v_x_persp_rot) * Cos(v_y_persp_rot) };
	v_look_vector = rot;
}

void Rotate (float x, float y)
{

	v_x_persp_rot += x * c_rot_x_speed;
	v_y_persp_rot += y * c_rot_x_speed;

	if(v_x_persp_rot > 360)
		v_x_persp_rot -= 360;

	if(v_y_persp_rot > 360)
		v_y_persp_rot -= 360;

	Refresh();
}

void Move(facing_t dir)
{
	switch(dir)
	{
	case left:
		v_camera_location.x += v_look_vector.z * c_move_speed;
		//vcamera_location.y += vlook_vector.y * move_speed;
		v_camera_location.z -= v_look_vector.x * c_move_speed;
		break;
	case right:
		v_camera_location.x -= v_look_vector.z * c_move_speed;
		//vcamera_location.y += vlook_vector.y * move_speed;
		v_camera_location.z += v_look_vector.x * c_move_speed;
		break;
	case forward:
		v_camera_location.x += v_look_vector.x * c_move_speed;
		//vcamera_location.y += vlook_vector.y * move_speed;
		v_camera_location.z += v_look_vector.z * c_move_speed;
		break;
	case backward:
		v_camera_location.x -= v_look_vector.x * c_move_speed;
		//vcamera_location.y -= vlook_vector.y * move_speed;
		v_camera_location.z -= v_look_vector.z * c_move_speed;
		break;
	case up:
		break;
	case down:
		break;
	}
}
