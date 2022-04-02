#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ArrayBuffer {
	unsigned int id;
	unsigned int size;

	ArrayBuffer(const void* data, unsigned int aSize) : size(aSize) {
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	~ArrayBuffer() {
		glDeleteBuffers(1, &id);
	}

	void bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
};
