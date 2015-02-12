/*
 * 
 */
#include "../../dj.h"
#include <glm/gtc/matrix_transform.hpp>

void display() {
	
	float ratio = v_window_width / (float)v_window_height;
	
	glViewport(0, 0, v_window_width, v_window_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	
	v_projection_matrix = glm::mat4();
	v_model_view_matrix = glm::mat4();

	// The View Matrix
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));
	
	// The Projection Matrix (ortho doesn't work)
	//~ v_projection_matrix = glm::ortho(-2.f, 2.f, -2.f, 2.f, 0.001f, 100000.0f);
	v_projection_matrix = glm::perspective(30.0f, ratio, 0.001f, 10000.0f);
	
	// The Model Matrix
	
	float x_rot_rads = v_x_persp_rot * M_PI / 180.0f;
	float y_rot_rads = v_y_persp_rot * M_PI / 180.0f;
	
	v_model_view_matrix = glm::rotate(v_model_view_matrix, x_rot_rads, glm::vec3(1.0f, 0, 0));
	v_model_view_matrix = glm::rotate(v_model_view_matrix, y_rot_rads, glm::vec3(0, 1.0f, 0));
	v_model_view_matrix = glm::scale(v_model_view_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
	
	// Model-View Matrix
	v_model_view_matrix = view * v_model_view_matrix;
	
	float *mvm = glm::value_ptr(v_model_view_matrix);	
	float *pm = glm::value_ptr(v_projection_matrix);
	
	glUseProgram(v_shader_mode);
	
	
	
	// Uniforms
	int loc = 0;
	loc = glGetUniformLocation(v_shader_mode, "ModelViewMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvm);
	else
		printf("Error Sending MVM Uniform\n");
		
	loc = glGetUniformLocation(v_shader_mode, "ProjectionMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, pm);
	else
		printf("Error Sending PM Uniform\n");
	
	loc = glGetUniformLocation(v_shader_mode, "NormalMatrix");
	if (loc >= 0) {
		glm::mat3 nm = glm::transpose(glm::inverse(glm::mat3(v_model_view_matrix)));
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(nm));
	} else
		printf("Error Sending Normal Matrix\n");
		
	loc = glGetUniformLocation(v_shader_mode, "LightPosition");
	if (loc >= 0)
		glUniform3fv(loc, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
	else
		printf("Error Sending Light Position\n");
		
	loc = glGetUniformLocation(v_shader_mode, "EyePosition");
	if (loc >= 0)
		glUniform3fv(loc, 1, glm::value_ptr(glm::inverse(v_model_view_matrix)[3]));
	else
		printf("Error Sending Eye Position\n");
		
	
	
	//~ // Ambient Lighting
	loc = glGetUniformLocation(v_shader_mode, "GlobalAmbient");
	if (loc >= 0)
		glUniform4f(loc, v_ambient_intensity, v_ambient_intensity, v_ambient_intensity, 1);
	else
		printf("Error Sending Ambient Light\n");
		
	
	// Vertex Data //
	glBindBuffer(GL_ARRAY_BUFFER, v_object_buffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12*sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12*sizeof(float), (void*)(sizeof(float) * 7));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 12*sizeof(float), (void*)(sizeof(float) * 4));
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
