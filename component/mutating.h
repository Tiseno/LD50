#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Mutating {
	bool v;
	static std::string NAME;
};

std::string Mutating::NAME = "Mutating";

std::ostream &operator<<(std::ostream &os, Mutating const& m) {
	return os << ANSI::YELLOW << Mutating::NAME << "{" << m.v << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Mutating const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Mutating::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

