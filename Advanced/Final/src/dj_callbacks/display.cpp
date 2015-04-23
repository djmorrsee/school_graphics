/*
 * 
 */
#include "../dj.h"
#include <glm/gtc/matrix_transform.hpp>

void display() {
		
	glViewport(0, 0, v_window_size.x, v_window_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(v_shader_programs[0]);
	
	// Model View Matrices
	glm::mat4 projection_matrix = glm::mat4();
	glm::mat4 model_view_matrix = glm::mat4();
	
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, .1), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));
	
	if (false)
		projection_matrix = glm::perspective(30.0f, 1.0f, 0.1f, 100.0f);
	else
		projection_matrix = glm::ortho(-v_dim, v_dim, -v_dim, v_dim, 1.0f / v_clipping_plane, v_clipping_plane);
	
	model_view_matrix = view * model_view_matrix;
	
	float x_rot_rads = v_x_rot * (M_PI / 180.0f);
	float y_rot_rads = v_y_rot * (M_PI / 180.0f);
		
	model_view_matrix = glm::rotate(model_view_matrix, x_rot_rads, glm::vec3(1.0f, 0, 0));
	model_view_matrix = glm::rotate(model_view_matrix, y_rot_rads, glm::vec3(0, 1.0f, 0));
	
	//~ model_view_matrix = glm::rotate(model_view_matrix, 90.0f, glm::vec3(1.0f, 0, 0));

	
	float *mvm = glm::value_ptr(model_view_matrix);
	float *pm = glm::value_ptr(projection_matrix);
	
	glm::mat4 model_view_projection_matrix = model_view_matrix * projection_matrix;
	float *mvpm = glm::value_ptr(model_view_projection_matrix);
	
	// Bind Uniforms
	int loc = 0;
	loc = glGetUniformLocation(v_shader_programs[0], "ModelViewMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvm);
	else
		printf("Error sending MVM\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "ProjectionMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, pm);
	else
		printf("Error sending PM\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "MVPMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvpm);
	else
		printf("Error sending MVPM");
	
	
	// Data Points
	GLuint vbo;
	glGenBuffers(1, &vbo);
	float points [] = {
		1, 1, 1
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLint posAttrib = glGetAttribLocation(v_shader_programs[0], "pos");
	glEnableVertexAttribArray(posAttrib);
	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_POINTS, 0, 3);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
