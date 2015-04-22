#include "../dj.h"

void Refresh ()
{
	//~ printf("X: %.2f Y: %.2f\n", v_x_rot, v_y_rot);
}

void Rotate (float x, float y)
{

	v_x_rot += x;
	v_y_rot += y;

	if(v_x_rot > 360)
		v_x_rot -= 360;

	if(v_y_rot > 360)
		v_y_rot -= 360;

	Refresh();
}

void Move(facing_t dir)
{
	
	switch(dir)
	{
		case left:
			//~ lights[0].position.x -= 1;
			v_x_rot += 1;
			break;
		case right:
			//~ lights[0].position.x += 1;
			v_x_rot -= 1;
			break;
		case forward:
			//~ lights[0].position.z -= 1;
			v_y_rot += 1;
			break;
		case backward:
			//~ lights[0].position.z += 1;
			v_y_rot -= 1;
			break;
		case up:
			break;
		case down:
			break;
	}
/*	switch(dir)
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
*/
}

