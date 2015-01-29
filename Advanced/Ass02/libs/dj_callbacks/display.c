/*
 * 
 */
#include "../../dj.h"

void display() {
	// Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	Project();
	
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
		glRotatef(v_x_persp_rot,1,0,0);
	  	glRotatef(v_y_persp_rot,0,1,0);
   	}

	

	// Lighting
	v_light_x = (int)(v_light_x + 1) % 360;
	v_light_y = (int)(v_light_y - 1) % 360;
	
	lights[0].position.x = Sin(v_light_x) * 5;
	lights[0].position.y = 2;
	lights[0].position.z = Cos(v_light_y) * 5;
	draw_light(0);

	// Set Shader Mode
	glUseProgram(v_shader_mode);
	
	// Scene
	glColor3f(1, 1, 1);
	
	glPushMatrix();
	glScalef(10, 1, 10);
	glCallList(v_models[0]);
	glPopMatrix();
	
	glUseProgram(0);
	
	// Log
	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("Homework 02");

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
