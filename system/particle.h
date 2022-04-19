#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../module/ecs/ecs.h"

#include "../frame_state.h"
#include "../component/velocity.h"
#include "../component/color.h"
#include "../component/particle.h"

struct ParticleSystem : System<FrameState> {
	ParticleSystem() : System{"ParticleSystem"} {}
	void update(Entities& entities, Components& components, FrameState& frameState) override {
		if (!components.hasPool<Particle>()) {
			return;
		}

		// TODO particle behavior
		for(auto& ssd : components.getPool<Particle>()->sparseSet.dense) {
			ssd.data.clock += frameState.time_delta;
			if (ssd.data.clock > ssd.data.ttl) {
				// TODO ML mark for deletion instead
				components.get<Velocity>(ssd.index)->v *= 0;
				components.get<Color>(ssd.index)->c *= 0;
			}
		}
	}
};
