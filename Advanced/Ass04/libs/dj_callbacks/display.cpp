/*
 * 
 */
#include "../../dj.h"

void display(GLFWwindow* window) {
	
	float ratio;
	int width, height;
	
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	
	float *mvm = glm::value_ptr(v_model_view_matrix);
	float *pm = glm::value_ptr(v_projection_matrix);
	
	glUseProgram(v_shader_mode);
	
	int loc;
	loc = glGetUniformLocation(v_shader_mode, "ModelViewMatrix");
	if (loc > 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvm);
		
	loc = glGetUniformLocation(v_shader_mode, "ProjectionMatrix");
	if (loc > 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, pm);
		
	
	
	// Redisplay done by caller
}
