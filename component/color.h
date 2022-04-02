#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Color {
	glm::vec3 c;
	static std::string NAME;
};

std::string Color::NAME = "Color";

std::ostream &operator<<(std::ostream &os, Color const& m) {
	return os << ANSI::YELLOW << Color::NAME << "{" << m.c.r << " " << m.c.g << " " << m.c.b << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Color const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Color::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

