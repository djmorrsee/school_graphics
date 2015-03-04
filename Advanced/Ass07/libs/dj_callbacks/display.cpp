/*
 * 
 */
#include "../../dj.h"
#include <glm/gtc/matrix_transform.hpp>

void display() {
		
	glViewport(0, 0, v_window_size.x, v_window_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	
	glm::mat4 v_model_view_matrix = glm::mat4();
	glm::mat4 v_projection_matrix = glm::mat4();

	// The View Matrix
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));
	
	// The Projection Matrix (ortho doesn't work)
	if(v_use_perspective)
		v_projection_matrix = glm::perspective(v_field_of_view, v_aspect_ratio, 1.0f / v_clipping_plane, v_clipping_plane);
	else
		v_projection_matrix = glm::ortho(-v_dim, v_dim, -v_dim, v_dim, 1.0f / v_clipping_plane, v_clipping_plane);
	
	
	v_model_view_matrix = view * v_model_view_matrix;

	// The Model Matrix
	float x_rot_rads = v_x_rot * M_PI / 180.0f;
	float y_rot_rads = v_y_rot * M_PI / 180.0f;
	
	v_model_view_matrix = glm::rotate(v_model_view_matrix, x_rot_rads, glm::vec3(1.0f, 0, 0));
	v_model_view_matrix = glm::rotate(v_model_view_matrix, y_rot_rads, glm::vec3(0, 1.0f, 0));
	
	// Model-View Matrix
	float *mvm = glm::value_ptr(v_model_view_matrix);	
	float *pm = glm::value_ptr(v_projection_matrix);
	
	glUseProgram(v_shader_programs[0]);
	
	// Uniforms
	int loc = 0;
	loc = glGetUniformLocation(v_shader_programs[0], "ModelViewMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, mvm);
	else
		printf("Error Sending MVM Uniform\n");
		
	loc = glGetUniformLocation(v_shader_programs[0], "ProjectionMatrix");
	if (loc >= 0)
		glUniformMatrix4fv(loc, 1, GL_FALSE, pm);
	else
		printf("Error Sending PM Uniform\n");
	
	//~ loc = glGetUniformLocation(v_shader_programs[0], "NormalMatrix");
	//~ if (loc >= 0) {
		//~ glm::mat3 nm = glm::transpose(glm::inverse(glm::mat3(v_model_view_matrix)));
		//~ glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(nm));
	//~ 
	//~ } else
		//~ printf("Error Sending Normal Matrix\n");
		//~ 
	//~ loc = glGetUniformLocation(v_shader_programs[0], "LightPosition");
	//~ if (loc >= 0)
		//~ glUniform3fv(loc, 1, glm::value_ptr(glm::vec3(1, 1, 1)));
	//~ else
		//~ printf("Error Sending Light Position\n");
	
	// Find Attributes
	GLint xyz_buffer = glGetAttribLocation(v_shader_programs[0], "XYZW");
	GLint rgb_buffer = glGetAttribLocation(v_shader_programs[0], "RGB");
	GLint tc_buffer = glGetAttribLocation(v_shader_programs[0], "TEX");	
	GLint norm_buffer = glGetAttribLocation(v_shader_programs[0], "NORM");
	
	// Vertex Postions
	glEnableVertexAttribArray(xyz_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, v_objects[0].pos_buffer);
	glVertexAttribPointer(xyz_buffer, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Vertex Colors
	glEnableVertexAttribArray(rgb_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, v_objects[0].rgb_buffer);
	glVertexAttribPointer(rgb_buffer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Vertex TCs
	glEnableVertexAttribArray(tc_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, v_objects[0].tc_buffer);
	glVertexAttribPointer(tc_buffer, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, v_objects[0].texture_id);
	GLuint texloc = glGetUniformLocation(v_shader_programs[0], "uSampler");
	glUniform1i(texloc, 0);
	
	// Vertex Normals
	glEnableVertexAttribArray(norm_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, v_objects[0].norm_buffer);
	glVertexAttribPointer(norm_buffer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 11808);

	glDisableVertexAttribArray(xyz_buffer);
	glDisableVertexAttribArray(rgb_buffer);
	glDisableVertexAttribArray(tc_buffer);
	glDisableVertexAttribArray(norm_buffer);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	if (v_current_shader_mode > 0) {
		glUseProgram(v_shader_programs[v_current_shader_mode]);
	
		//  Set offsets
		int id = glGetUniformLocation(v_shader_programs[1],"dX");
		if (id>=0) glUniform1f(id,1.0/v_window_size.x);
		id = glGetUniformLocation(v_shader_programs[1],"dY");
		if (id>=0) glUniform1f(id,1.0/v_window_size.y);

		//  Disable depth
		glDisable(GL_DEPTH_TEST);

		//  Indentity projections
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		int k;
		int N = 1; // passes
		//  Shader passes
		for (k=0;k<N;k++)
		{
			glBindTexture(GL_TEXTURE_2D,v_textures[0]);
			//  Copy original scene to texture
			glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,0,0,v_window_size.x,v_window_size.y,0);

			//  Redraw the texture
			glClear(GL_COLOR_BUFFER_BIT);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex2f(-1,-1);
			glTexCoord2f(0,1); glVertex2f(-1,+1);
			glTexCoord2f(1,1); glVertex2f(+1,+1);
			glTexCoord2f(1,0); glVertex2f(+1,-1);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
				
	}
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
