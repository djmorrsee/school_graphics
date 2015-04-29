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
	glm::mat4 view = glm::mat4();
	
	
	float x_rot_rads = v_x_rot * (M_PI / 180.0f);
	float y_rot_rads = v_y_rot * (M_PI / 180.0f);
		
	model_view_matrix = glm::rotate(model_view_matrix, x_rot_rads, glm::vec3(1.0f, 0, 0));
	model_view_matrix = glm::rotate(model_view_matrix, y_rot_rads, glm::vec3(0, 1.0f, 0));
	
	//~ model_view_matrix = glm::rotate(model_view_matrix, 90.0f, glm::vec3(1.0f, 0, 0));
	
	if (false) {
		view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));
		model_view_matrix = view * model_view_matrix;

		//~ projection_matrix = glm::perspective(30.0f, 1.0f, 0.01f, 1000.0f);
	}
	else
		projection_matrix = glm::ortho(-v_dim, v_dim, -v_dim, v_dim, 1.0f / v_clipping_plane, v_clipping_plane);
	


	
	float *mvm = glm::value_ptr(model_view_matrix);
	float *pm = glm::value_ptr(projection_matrix);
	
	glm::mat4 model_view_projection_matrix = model_view_matrix * projection_matrix;
	float *mvpm = glm::value_ptr(model_view_projection_matrix);
	
	// Bind Uniforms
	int loc = 0;
	loc = glGetUniformLocation(v_shader_programs[0], "ModelViewMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvm);
	//~ else
		//~ printf("Error sending MVM\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "ProjectionMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, pm);
	//~ else
		//~ printf("Error sending PM\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "MVPMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvpm);
	else
		printf("Error sending MVPM");
		
	std::vector<float> ids = v_main_chunk.flatIDMap();
	float test[] = { 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 
					
				};
	loc = glGetUniformLocation(v_shader_programs[0], "Cube_IDs");
	if (loc >= 0)
		//~ glUniform1fv(loc, 1, &ids[0]);
		glUniform1fv(loc, 256, test);

	else
		printf("Error sending IDs");
	
	// Texture
	//~ glActiveTexture(GL_TEXTURE0);
	//~ glBindTexture(GL_TEXTURE_1D, v_block_texture_id);
	//~ loc = glGetUniformLocation(v_shader_programs[0], "chunk_sampler");
	//~ if (loc >= 0)
		//~ glUniform1i(loc, 0); // Texture ID?
	//~ elses
		//~ printf("Error sending texture\n");
	
	
	// Data Points
	GLuint vbo;
	glGenBuffers(1, &vbo);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	std::vector<float> v = v_main_chunk.flatPositionMap();
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), &v[0], GL_STATIC_DRAW);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLint posAttrib = glGetAttribLocation(v_shader_programs[0], "pos");
	glEnableVertexAttribArray(posAttrib);
	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	
	// Draw Points
	glDrawArrays(GL_POINTS, 0, v_chunk_dim*v_chunk_dim*v_chunk_height);
	
	glUseProgram(0);

	glColor3f(1, 1, 1);
	glWindowPos2i(5, 5);
	Print("%i", FramesPerSecond());

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
