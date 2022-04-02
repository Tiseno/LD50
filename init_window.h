#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

GLFWwindow* init_window() {
	if (!glfwInit()) {
		cout << "Could not init glfw!" << endl;
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	auto hw = 1024;
	auto window = glfwCreateWindow(hw, hw, "", nullptr, nullptr);

	if (!window) {
		cout << "Could not create glfw window!" << endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	auto glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		cout << "Could not init glew! " << glewGetErrorString(glewInitResult) << endl;
		glfwTerminate();
		return nullptr;
	}
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);


	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
	printf("Glsl version supported by this platform (%s): \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    return window;
}
