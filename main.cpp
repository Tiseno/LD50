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

#include "init_window.h"
#include "system/movement.h"
#include "system/create_entities.h"
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
}

ECS<FrameState> ecs;
FrameState frameState;

// How do we make this better and not reliant on global variables?
void keyCallback(GLFWwindow* window, int key, int, int action, int){
	if(action == GLFW_PRESS) {
		if(key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, 1);
		} else if(key == GLFW_KEY_SPACE) {
				printEcsInfo(ecs);
				std::cout << "Last frametime " << (1.0/frameState.time_delta) << "\n";
		} else if(key == GLFW_KEY_D) {
			auto numberToRemove = 5000;
			for(int i = 0; i < numberToRemove; i++) {
				removeRandomEntity(ecs.entities, ecs.components);
			}
			std::cout << "Removed " << numberToRemove << " entities\n";
			printEcsInfo(ecs);
		}
	}
}

int main() {
	auto window = init_window();
	if (window == nullptr) {
		return 1;
	}

	ecs.systems.push_back(new MovementSystem());
	ecs.systems.push_back(new CreateEntitiesSystem());
	ecs.systems.push_back(new DrawingSystem(window));

	for(size_t i = 0; i < 10000; i++) {
		createRandomEntity(ecs.entities, ecs.components);
	}

	glfwSetKeyCallback(window, keyCallback);

	auto prevTime = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		auto nowTime = std::chrono::steady_clock::now();
		double time_delta = std::chrono::duration<double>(nowTime - prevTime).count();
		prevTime = nowTime;
		frameState = {time_delta};
		ecs.update(frameState);
	}
	return 0;
}
