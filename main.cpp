#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

#include "module/ecs/ecs.h"
#include "module/ecs/ansi.h"

#include "frame_state.h"
#include "component/position.h"
#include "component/velocity.h"
#include "component/acceleration.h"
#include "component/color.h"
#include "component/size.h"
#include "component/mutating.h"

#include "init_window.h"
#include "system/movement.h"
#include "system/mutating.h"
#include "system/drawing.h"

void printEcsInfo(ECS<FrameState>& ecs) {
	std::cout << "There are " << ecs.entities.size() << " entities\n";
	std::cout << "\tReserved space for " << ecs.entities.entities.capacity() << "\n";
	std::cout << "\tUsed space of " << ecs.entities.entities.size() << "\n";
	std::cout << "\tFree indexes " << ecs.entities.freeEntityIndexes.size() << "\n";
}

void removeRandomEntity(Entities& entities, Components& components) {
	Entity e = entities.getRandom();
	entities.remove(e);
	components.remove<Position>(e.index);
	components.remove<Velocity>(e.index);
	components.remove<Acceleration>(e.index);
	components.remove<Color>(e.index);
	components.remove<Size>(e.index);
	components.remove<Mutating>(e.index);
}

ECS<FrameState> ecs;
FrameState frameState;

// How do we make this better and not reliant on global variables?
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto press = action == GLFW_PRESS;
	if(press && key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, 1);
	} else if(press && key == GLFW_KEY_SPACE) {
			printEcsInfo(ecs);
			std::cout << "Last frametime " << (1.0/frameState.time_delta) << "\n";
	} else {
		std::cout << ANSI::GRAY << "glfw key callback\n";
		std::cout << "\tkey:      " << key << "\n";
		std::cout << "\tscancode: " << scancode << "\n";
		std::cout << "\taction:   " << action << "\n";
		std::cout << "\tmods:     " << mods << "\n" << ANSI::RESET;
	}
}

void mouseButtonCallBack(GLFWwindow* window, int button, int action, int mods) {
	std::cout << ANSI::GRAY << "glfw mouse button callback\n";
	std::cout << "\tbutton:   " << button << "\n";
	std::cout << "\taction:   " << action << "\n";
	std::cout << "\tmods:     " << mods << "\n";
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	std::cout << "\tposition: {" << x << "," << y << "}\n" << ANSI::RESET;
}

Entity createPlayer(ECS<FrameState>& ecs) {
	Entity e = ecs.entities.create();
	ecs.components.assign(e.index, Position{glm::vec2{0, 0}});
	ecs.components.assign(e.index, Velocity{glm::vec2{0, 0}});
	ecs.components.assign(e.index, Acceleration{glm::vec2{0, 0}});
	ecs.components.assign(e.index, Size{5});
	ecs.components.assign(e.index, Color{glm::vec3{1,1,0}});
	return e;
}

void createMutatingEntity(ECS<FrameState>& ecs) {
	Entity e = ecs.entities.create();
	ecs.components.assign(e.index, Position{glm::vec2{rf(-100, 100)/100, rf(-100, 100)/100}});
	ecs.components.assign(e.index, Mutating{true});
}

std::ostream &operator<<(std::ostream &os, glm::vec2 const& m) {
	return os << ANSI::YELLOW << "glm::vec2" << "{" << m.x << " " << m.y << "}" << ANSI::RESET;
}

glm::vec2 normOrZero(glm::vec2 v) {
	return v.x == 0 && v.y == 0 ? v : glm::normalize(v);
}

void playerControls(GLFWwindow* window, ECS<FrameState>& ecs, Entity player) {
	auto pressDirection = glm::vec2{
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ?  1 : 0 + glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? -1 : 0,
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ?  1 : 0 + glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? -1 : 0
	};
	auto pressNorm = normOrZero(pressDirection);
	auto vel = ecs.components.get<Velocity>(player.index)->v;
	auto velNorm = normOrZero(vel);
	const auto VEL_MAX = 1.5;
	auto velMaxNorm = glm::vec2{vel.x/VEL_MAX, vel.y/VEL_MAX};
	auto dot = glm::dot(velNorm, pressNorm);
	if (dot > 0) {
		pressNorm.x = pressNorm.x - velMaxNorm.x;
		pressNorm.y = pressNorm.y - velMaxNorm.y;
	}

	const auto ACC_MAX = 20.0;
	glm::vec2 acc;
	acc.x = (pressNorm.x) * ACC_MAX;
	acc.y = (pressNorm.y) * ACC_MAX;
	ecs.components.get<Acceleration>(player.index)->v = acc;
}

int main() {
	auto window = init_window();
	if (window == nullptr) {
		return 1;
	}

	ecs.systems.push_back(new MovementSystem());
	ecs.systems.push_back(new MutatingSystem());
	ecs.systems.push_back(new DrawingSystem(window));

	for(size_t i = 0; i < 10000; i++) {
		createMutatingEntity(ecs);
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallBack);

	Entity player = createPlayer(ecs);

	auto prevTime = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		playerControls(window, ecs, player);
		auto nowTime = std::chrono::steady_clock::now();
		double time_delta = std::chrono::duration<double>(nowTime - prevTime).count();
		prevTime = nowTime;
		frameState = {time_delta};
		ecs.update(frameState);
	}
	return 0;
}
