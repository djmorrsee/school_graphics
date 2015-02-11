/*
 * 
 */
#include "dj.h"

void SetupGLFW(GLFWwindow *window);

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


	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::vector<glm::vec4> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> tcs;
	
	load_obj("libs/dj_resources/models/monkeybox.obj", verts, norms, colors, tcs);

	while(!glfwWindowShouldClose(window)) 
	{
			display(window);
			glfwSwapBuffers(window);
			glfwPollEvents();
	}
}


