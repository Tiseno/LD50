#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Position {
	glm::vec2 v;
	static std::string NAME;
};

std::string Position::NAME = "Position";

std::ostream &operator<<(std::ostream &os, Position const& m) {
	return os << ANSI::YELLOW << Position::NAME << "{" << m.v.x << " " << m.v.y << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Position const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Position::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

