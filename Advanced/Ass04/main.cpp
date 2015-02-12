/*
 * 
 */
#include "dj.h"

void SetupGLFW(GLFWwindow *window);

void error_callback(int error, const char* description) {
	printf("%s", description);
	printf("\n");
}

int main(int argc, char* argv[]) {
	GLFWwindow *main_window;
	
	SetupGLFW(main_window);
	printf("%d", main_window == NULL);

	glfwDestroyWindow(main_window);

	glfwTerminate();
	return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_W)
			v_x_persp_rot += 1;
		else if (key == GLFW_KEY_S)
			v_x_persp_rot -= 1;
		else if (key == GLFW_KEY_A)
			v_y_persp_rot += 1;
		else if (key == GLFW_KEY_D)
			v_y_persp_rot -= 1;
		
	
}

const int cube_size=36;
const float cube_data[] =  // Vertex data
{
//  X  Y  Z  W   Nx Ny Nz    R G B   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,  0,0,
   //  Back
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,  0,1,
   //  Right
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,  1,0,
   //  Left
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,  0,0,
   //  Top
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,  0,1,
   //  Bottom
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,  1,1,
   };

//
//  Cube vertex buffer object
//
void InitCube()
{
   //  Copy data to vertex buffer object
   glGenBuffers(1,&v_object_buffer);
   glBindBuffer(GL_ARRAY_BUFFER,v_object_buffer);
   glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);

   //  Unbind this buffer
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

void InitMonkey()
{   
	//  Copy data to vertex buffer object
    glGenBuffers(1,&v_object_buffer);
    glBindBuffer(GL_ARRAY_BUFFER,v_object_buffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(v_data_buffer),v_data_buffer,GL_STATIC_DRAW);

	//  Unbind this buffer
	glBindBuffer(GL_ARRAY_BUFFER,0);
	
}

void SetupGLFW(GLFWwindow *window) {

	// GL Settings //
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window = glfwCreateWindow(640, 480, "GLFW Success", NULL, NULL);
	
	if (!window) {
		printf("Error creating window context\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetErrorCallback(error_callback);

	
	// Create Object Buffer From OBJ File
	load_obj("libs/dj_resources/models/monkeybox.obj", v_data_buffer);

	printf("Testing\n");
	printf("wat %d\n", sizeof(v_data_buffer));
		
	//~ InitCube();
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	v_shader_mode = CreateShaderProg("libs/dj_resources/shaders/gl430.vert", "libs/dj_resources/shaders/gl430.frag"); 

	while(!glfwWindowShouldClose(window)) 
	{
			display(window);
			glfwSwapBuffers(window);
			glfwPollEvents();
	}
}


