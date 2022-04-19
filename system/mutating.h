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
#include "../component/mutating.h"

#include "../util.h"

void giveRandomComponent(EntityIndex index, Entities& entities, Components& components) {
	auto f = rf(0,1000);
	if(f < 20) {
		components.assign(index, Velocity{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	} else if(20 <= f && f < 40) {
		components.assign(index, Acceleration{glm::vec2{rf(-10, 10)/100, rf(-10, 10)/100}});
	} else if(40 <= f && f < 60) {
		components.assign(index, Color{glm::vec3{rf(20, 100)/100, rf(20, 100)/100, rf(20, 100)/100}});
	} else if(60 <= f && f < 80) {
		components.assign(index, Size{rf(20,50)/10});
	} else if(80 <= f && f < 120) {
		components.remove<Velocity>(index);
	} else if(120 <= f && f < 140) {
		components.remove<Acceleration>(index);
	} else if(140 <= f && f < 160) {
		components.remove<Color>(index);
	} else if(160 <= f && f < 180) {
		components.remove<Size>(index);
	}
}

struct MutatingSystem : System<FrameState> {
	MutatingSystem() : System{"MutatingSystem"} {}
	void update(Entities& entities, Components& components, FrameState& frameState) override {
		if (!components.hasPool<Mutating>()) {
			return;
		}
		if (components.getPool<Mutating>()->sparseSet.dense.size() == 0) {
			return;
		}
		for(size_t i = 0; i < static_cast<size_t>(frameState.time_delta * 4000); i++) {
			auto& ssd = components.getPool<Mutating>()->sparseSet.dense[rand() % components.getPool<Mutating>()->sparseSet.dense.size()];
			giveRandomComponent(ssd.index, entities, components);
		}
	}
};
