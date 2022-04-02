#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <unordered_set>

struct ShaderProgram {
	unsigned int id;
	std::string name;

	static std::unordered_set<ShaderProgram*> shaders;

	static void reload() {
		for(auto sh : shaders) {
			sh->compile();
		}
	}

	explicit ShaderProgram(std::string const& n) : id(0), name(n) {
		compile();
		shaders.insert(this);
	}

	~ShaderProgram() {
		if(id != 0) {
			glDeleteProgram(id);
		}
		shaders.erase(this);
	}

	void compile() {
		if(id != 0) {
			glDeleteProgram(id);
		}
		id = glCreateProgram();
		auto vertShaderId = compileShader(GL_VERTEX_SHADER, name);
		if(vertShaderId < 1) {
			std::cout << "Error compiling '" << name << "' vert shader.\n";
			return;
		}

		auto fragShaderId = compileShader(GL_FRAGMENT_SHADER, name);
		if(fragShaderId < 1) {
			std::cout << "Error compiling '" << name << "' frag shader.\n";
			return;
		}

		glAttachShader(id, vertShaderId);
		glAttachShader(id, fragShaderId);
		glLinkProgram(id);
		glValidateProgram(id);

		glDeleteShader(vertShaderId);
		glDeleteShader(fragShaderId);
		bind();

		std::cout << "Compiled shader '" << name << "' (" << id << ")\n";
	}

	void bind() {
		glUseProgram(id);
	}

	static std::string shaderTypeToEnding(unsigned int shaderType) {
		switch(shaderType) {
			case GL_COMPUTE_SHADER:
				return ".comp";
			case GL_VERTEX_SHADER:
				return ".vert";
			case GL_TESS_CONTROL_SHADER:
				return ".tesc";
			case GL_TESS_EVALUATION_SHADER:
				return ".tese";
			case GL_GEOMETRY_SHADER:
				return ".geom";
			case GL_FRAGMENT_SHADER:
				return ".frag";
			default:
				throw "Not an openGL shader";
		}
	}

	static unsigned int compileShader(unsigned int shaderType, std::string const& name) {
		std::string shaderPath = "./system/shader/" + name + shaderTypeToEnding(shaderType);
		std::ifstream ifs(shaderPath);
		const std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

		unsigned int shaderId = glCreateShader(shaderType);
		const char * source = content.c_str();
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);

		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

			GLchar * strInfoLog = new GLchar[length + 1];
			glGetShaderInfoLog(shaderId, length, &length, strInfoLog);

			std::cout << "Error compiling shader " << shaderPath << ": " << strInfoLog << "\n";
			delete[] strInfoLog;
			return -1;
		}
		return shaderId;
	}
};

std::unordered_set<ShaderProgram*> ShaderProgram::shaders;

