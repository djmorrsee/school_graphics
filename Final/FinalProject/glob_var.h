/*
 * Global Variables for the Project
 */
#ifndef __dj_vars
#define __dj_vars

// Viewport 
extern float vfield_of_view;
extern float vaspect_ratio;
extern float vclipping_plane;

// User View Rotation
extern float vx_persp_rot;
extern float vy_persp_rot;

// User View LookVector
extern float vlook_vector[3];

// Rotate the screen (alters persp_rot and vlook_vector)

// User View Location
extern float vcamera_location[3];

float* get_look_position();
// Moves the Camera relative to look direction

#endif
