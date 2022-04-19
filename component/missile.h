#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Missile {
	float ttl;
	float clock;
	bool exploded;
	static std::string NAME;
};

std::string Missile::NAME = "Missile";

std::ostream &operator<<(std::ostream &os, Missile const& m) {
	return os << ANSI::YELLOW << Missile::NAME << "{" << m.ttl << " " << m.clock << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Missile const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Missile::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

