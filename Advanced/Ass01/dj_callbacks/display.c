/*
 * 
 */
#include "../dj.h"

void display() {
	// Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// Set Shader Mode
	use_shader(v_shader_mode);

	Project();

	// Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);

	// Undo previous transformations
	glLoadIdentity();

	// Check if we need to move //
	if (v_move_forward)
		Move(forward);
	else if (v_move_backward)
		Move(backward);
	if (v_move_left)
		Move(left);
	else if (v_move_right)
		Move(right);
	glRotatef(90, 1, 0, 0);
	   //  Perspective - set eye position
   	if (v_use_perspective)
   	{
      		double Ex = -2*v_dim*Sin(v_y_persp_rot)*Cos(v_x_persp_rot);
      		double Ey = +2*v_dim        *Sin(v_x_persp_rot);
      		double Ez = +2*v_dim*Cos(v_y_persp_rot)*Cos(v_x_persp_rot);
      		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(v_x_persp_rot),0);
   	}
  	 //  Orthogonal - set world orientation
	else
	{
		glTranslatef(0, 0, 2);
		glRotatef(v_x_persp_rot,1,0,0);
      		glRotatef(v_y_persp_rot,0,1,0);
   	}

	// Scene

	glCallList(v_models[0]);

	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Homework 01");

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
