/*
 * Global Variables for the Project
 */
#ifndef __dj_vars
#define __dj_vars

#include "dj_structures.h"
#include <stdbool.h>

// Motion
extern bool v_move_forward;
extern bool v_move_backward;
extern bool v_move_left;
extern bool v_move_right;

// View port
extern int v_window_width;
extern int v_window_height;
extern float v_field_of_view;
extern float v_aspect_ratio;
extern float v_clipping_plane;

// User View Rotation
extern bool v_rotate_view;

extern float v_x_persp_rot;
extern float v_y_persp_rot;

// User View LookVector
extern vector3 v_look_vector;

// User View Location
extern vector3 v_camera_location;

// Returns the vector sum of vlook_vector and vcamera_location
vector3 get_look_position();

// Lighting
extern light lights[8];

#endif
