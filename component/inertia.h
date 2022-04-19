#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

struct Inertia {
	double v;
	static std::string NAME;
};

std::string Inertia::NAME = "Inertia";

std::ostream &operator<<(std::ostream &os, Inertia const& m) {
	return os << ANSI::YELLOW << Inertia::NAME << "{" << m.v << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Inertia const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Inertia::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

