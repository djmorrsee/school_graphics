/*
 * 
 */
#include "dj.h"

void display() 
{
	// Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	// Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	// Set Shader Mode
	use_shader(vshader_mode);

	Project();

	// Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	
	// Undo previous transformations
	glLoadIdentity();

	// Check if we need to move //
	if(v_move_forward)
		Move(forward);
	else if (v_move_backward)
		Move(backward);
	if(v_move_left)
		Move(left);
	else if (v_move_right)
		Move(right);

	// Viewport
	vector3 look_pos = get_look_position();
	gluLookAt(v_camera_location.x,v_camera_location.y,v_camera_location.z , look_pos.x,look_pos.y,look_pos.z , 0,1,0);

	// Lighting
	vector3 z = {.x=0, .y=0, .z=-5};
	vector4 r = {.x = .5, .y=.5,.z=.5,.a=1};

	set_light(0, z, r);

	z.x = 1.5; z.y = -1; z.z = 1;
	r.x = .7; r.y = .3; r.z = .3;

	set_light(1, z, r);
	draw_light(0);
	draw_light(1);

	// Scene
	glColor3f(.8,.8,.8);
	draw_structure();
	glTranslatef(0, -1, 0);

	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Shader Mode %d", vshader_mode);


	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
