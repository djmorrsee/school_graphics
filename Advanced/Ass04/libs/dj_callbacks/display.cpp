/*
 * 
 */
#include "../../dj.h"
#include <glm/gtc/matrix_transform.hpp>

void display(GLFWwindow* window) {
	
	float ratio;
	int width, height;
	
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	
	v_projection_matrix = glm::mat4();
	v_model_view_matrix = glm::mat4();

	// The View Matrix
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));
	
	// The Projection Matrix
	v_projection_matrix = glm::ortho(-2.f, 2.f, -2.f, 2.f, 0.001f, 100000.0f) * view;
	//~ v_projection_matrix = glm::perspective(30.0f, ratio, 0.001f, 10000.0f) * view;
	
	// The Model Matrix
	v_model_view_matrix = glm::rotate(v_model_view_matrix, v_x_persp_rot, glm::vec3(1.0f, 0, 0));
	v_model_view_matrix = glm::rotate(v_model_view_matrix, v_y_persp_rot, glm::vec3(0, 1.0f, 0));
	v_model_view_matrix = glm::scale(v_model_view_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
	
	float *mvm = glm::value_ptr(v_model_view_matrix);	
	float *pm = glm::value_ptr(v_projection_matrix);
	
	glUseProgram(v_shader_mode);
	
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
		
	glBindBuffer(GL_ARRAY_BUFFER, v_object_buffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
	//~ 
	//~ glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glFlush();
	// Redisplay done by caller
}
