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
#include "../component/missile.h"
#include "../component/particle.h"

#include "../util.h"

void createRandomParticle(Entities& entities, Components& components, glm::vec2 position) {
	Entity e = entities.create();
	components.assign(e.index, Position{position});
	components.assign(e.index, Velocity{normOrZero({rf(-100,100), rf(-100,100)})});
	components.assign(e.index, Size{2});
	components.assign(e.index, Color{glm::vec3{0.8,0.8,0}});
	components.assign(e.index, Particle{ParticleBehavior::Straight, 1, 0});
}

struct MissileSystem : System<FrameState> {
	MissileSystem() : System{"MissileSystem"} {}
	void update(Entities& entities, Components& components, FrameState& frameState) override {
		if (!components.hasPool<Missile>()) {
			return;
		}

		for(auto& ssd : components.getPool<Missile>()->sparseSet.dense) {
			if (ssd.data.exploded) {
				continue;
			}
			ssd.data.clock += frameState.time_delta;
			if (ssd.data.clock > ssd.data.ttl) {
				components.get<Velocity>(ssd.index)->v *= 0;
				components.get<Color>(ssd.index)->c += frameState.time_delta * 2;
			}
			if (ssd.data.clock > (ssd.data.ttl + 0.3)) {
				// TODO ML mark for deletion instead
				components.get<Color>(ssd.index)->c.r = 0;
				components.get<Color>(ssd.index)->c.g = 0;
				components.get<Color>(ssd.index)->c.b = 0;
				ssd.data.exploded = true;
				for(size_t i = 0; i < 100; i++) {
					createRandomParticle(entities, components, components.get<Position>(ssd.index)->v);
				}
			}
		}
	}
};
