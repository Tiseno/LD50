#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../module/ecs/ecs.h"

#include "../frame_state.h"
#include "../component/position.h"
#include "../component/color.h"
#include "../component/size.h"

#include "shader.h"
#include "array_buffer.h"

float onePoint[] = { 0.0, 0.0 };

struct DrawingSystem : System<FrameState> {
	GLFWwindow* window;
	ShaderProgram pointShader;
	ArrayBuffer pointArrayBuffer;

	explicit DrawingSystem(GLFWwindow* _window) :
		System{"DrawingSystem"},
		window(_window),
		pointShader("point"),
		pointArrayBuffer(onePoint, sizeof(onePoint)) {}

	void update(Entities& entities, Components& components, FrameState& frameState) override {
		if (!components.hasPool<Position>()) {
			return;
		}
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		pointShader.bind();
		pointArrayBuffer.bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		for(auto& ssd : components.getPool<Position>()->sparseSet.dense) {
			auto position = &ssd.data;
			glUniform1f(glGetUniformLocation(pointShader.id, "time"), frameState.time_delta);
			glUniform2f(glGetUniformLocation(pointShader.id, "position"), position->v.x, position->v.y);
			auto color = components.get<Color>(ssd.index);
			if(color != nullptr) {
				glUniform3f(glGetUniformLocation(pointShader.id, "color"), color->c.r, color->c.g, color->c.b);
			} else {
				glUniform3f(glGetUniformLocation(pointShader.id, "color"), 0.2, 0.2, 0.2);
			}
			auto size = components.get<Size>(ssd.index);
			if(size != nullptr) {
				glUniform1f(glGetUniformLocation(pointShader.id, "size"), size->size);
			} else {
				glUniform1f(glGetUniformLocation(pointShader.id, "size"), 1);
			}
			glDrawArrays(GL_POINTS, 0, 1);
		}
		glfwSwapBuffers(window);
		while (GLenum error = glGetError()) {
			std::cout << "GLERROR " << error << "\n";
		}
	}
};

