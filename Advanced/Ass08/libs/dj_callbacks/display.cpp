/*
 * 
 */
#include "../../dj.h"
#include <glm/gtc/matrix_transform.hpp>

void display() {
		
	glViewport(0, 0, v_window_size.x, v_window_size.y);
	
	if (v_first_draw) {
		glClear(GL_COLOR_BUFFER_BIT);
	
		glBindTexture(GL_TEXTURE_2D, v_textures[0]);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, v_window_size.x, v_window_size.y, 0);
		
		glFlush();
		glutSwapBuffers();	
		glutPostRedisplay();
		v_first_draw = false;
		return;
	}
	
	if (v_clear_draw) {
		glClear(GL_COLOR_BUFFER_BIT);
		v_clear_draw = false;
	}
	
	glUseProgram(v_shader_programs[0]);
	glEnable(GL_TEXTURE_2D);
			
	int color = v_cursor_down ? v_draw_color : 0;
	
	// Uniforms
	int loc = 0;
	loc = glGetUniformLocation(v_shader_programs[0], "cursor_x");
	if (loc >= 0)
		glUniform1i(loc, v_cursor_x);
	else
		printf("Error Sending X Cursor\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "cursor_y");
	if (loc >= 0)
		glUniform1i(loc, v_window_size.y - v_cursor_y);
	else
		printf("Error Sending Y Cursor\n");
	
	loc = glGetUniformLocation(v_shader_programs[0], "window_x");
	if (loc >= 0)
		glUniform1i(loc, v_window_size.x);
	else
		printf("Error Sending X Cursor\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "window_y");
	if (loc >= 0)
		glUniform1i(loc, v_window_size.y);
	else
		printf("Error Sending Y Cursor\n");
	
	loc = glGetUniformLocation(v_shader_programs[0], "draw");
	if (loc >= 0)
		glUniform1i(loc, color);
	//~ else
		//~ printf("Error Sending Color Val\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "canvas");
	if (loc >= 0)
		glUniform1i(loc, v_textures[0]);
	else
		printf("Error Sending Texture\n");

	glBindTexture(GL_TEXTURE_2D, v_textures[0]);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, v_window_size.x, v_window_size.y, 0);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(-1,-1);
	glTexCoord2f(0,1); glVertex2f(-1,+1);
	glTexCoord2f(1,1); glVertex2f(+1,+1);
	glTexCoord2f(1,0); glVertex2f(+1,-1);
	glEnd();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
