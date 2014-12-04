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
	vector3 z = {.x=3, .y=0, .z=0};
	vector4 r = {.x = 1, .y=0,.z=0,.a=1};

	set_light(0, z, r);
	draw_light(0);

	// Scene
	glColor3f(.8,.8,.8);
	draw_structure();
	glTranslatef(0, -1, 0);

	glFrontFace(GL_CW);
	glutSolidTeapot(0.5);
	glFrontFace(GL_CCW);

	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Rotation: %.3f %.3f %.3f", v_look_vector.x, v_look_vector.y, v_look_vector.z);


	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
