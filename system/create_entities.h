#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../module/ecs/ecs.h"

#include "../frame_state.h"
#include "../component/position.h"
#include "../component/velocity.h"
#include "../component/acceleration.h"
#include "../component/color.h"
#include "../component/size.h"

float rf(int min, int max) {
	return (float)(min + (rand() % (max - min)));
}

void giveRandomComponent(Entities& entities, Components& components) {
	Entity e = entities.getRandom();
	auto f = rf(0,100);
	if(f < 20) {
		components.assign(e.index, Velocity{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	} else if(f < 40) {
		components.assign(e.index, Acceleration{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	} else if(f < 60) {
		components.assign(e.index, Color{glm::vec3{rf(20, 100)/100, rf(20, 100)/100, rf(20, 100)/100}});
	} else if(f < 80) {
		components.assign(e.index, Size{rf(20,50)/10});
	}
}

void createRandomEntity(Entities& entities, Components& components) {
	Entity e = entities.create();
	components.assign(e.index, Position{glm::vec2{rf(-100, 100)/100, rf(-100, 100)/100}});
	// components.assign(e.index, Velocity{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	// components.assign(e.index, Acceleration{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	// components.assign(e.index, Color{glm::vec3{rf(20, 100)/100, rf(20, 100)/100, rf(20, 100)/100}});
	// components.assign(e.index, Size{rf(20,50)/10});
}

struct CreateEntitiesSystem : System<FrameState> {
	CreateEntitiesSystem() : System{"CreateEntitiesSystem"} {}
	void update(Entities& entities, Components& components, FrameState& frameState) override {
		for(int i = 0; i < 100; i++) {
			giveRandomComponent(entities, components);
			// createRandomEntity(entities, components);
		}
	}
};
