#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Acceleration {
	glm::vec2 v;
	static std::string NAME;
};

std::string Acceleration::NAME = "Acceleration";

std::ostream &operator<<(std::ostream &os, Acceleration const& m) {
	return os << ANSI::YELLOW << Acceleration::NAME << "{" << m.v.x << " " << m.v.y << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Acceleration const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Acceleration::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

