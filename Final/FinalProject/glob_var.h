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
void Rotate(float x, float y);

// User View Location
extern float vcamera_location[3];

// Moves the Camera relative to look direction
void Move(facing_t dir);

#endif
