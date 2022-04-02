#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Velocity {
	glm::vec2 v;
	static std::string NAME;
};

std::string Velocity::NAME = "Velocity";

std::ostream &operator<<(std::ostream &os, Velocity const& m) {
	return os << ANSI::YELLOW << Velocity::NAME << "{" << m.v.x << " " << m.v.y << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Velocity const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Velocity::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

