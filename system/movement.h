#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../module/ecs/ecs.h"

#include "../frame_state.h"
#include "../component/position.h"
#include "../component/velocity.h"
#include "../component/acceleration.h"

struct MovementSystem : System<FrameState> {
	MovementSystem() : System{"MovementSystem"} {}
	void update(Entities& entities, Components& components, FrameState& frameState) override {
		if (!components.hasPool<Velocity>() || !components.hasPool<Position>()) {
			return;
		}
		for(auto& ssd : components.getPool<Velocity>()->sparseSet.dense) {
			auto velocity = &ssd.data;
			auto position = components.get<Position>(ssd.index);
			auto acceleration = components.get<Acceleration>(ssd.index);

			if(position != nullptr) {
				if(acceleration != nullptr) {
					velocity->v.x += acceleration->v.x * frameState.time_delta;
					velocity->v.y += acceleration->v.y * frameState.time_delta;
				}

				position->v.x += velocity->v.x * frameState.time_delta;
				position->v.y += velocity->v.y * frameState.time_delta;
				if(position->v.x > 1) {
					velocity->v.x = -velocity->v.x;
					position->v.x = 1;
				}
				if(position->v.x < -1) {
					velocity->v.x = -velocity->v.x;
					position->v.x = -1;
				}
				if(position->v.y > 1) {
					velocity->v.y = -velocity->v.y;
					position->v.y = 1;
				}
				if(position->v.y < -1) {
					velocity->v.y = -velocity->v.y;
					position->v.y = -1;
				}
			}
		}
	}
};

