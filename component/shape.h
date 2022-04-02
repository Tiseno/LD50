#pragma once

#include <iostream>

#include "../module/ecs/ansi.h"

enum Type {
	TRIANGLE
};

struct Shape {
	Type t;
	static std::string NAME;
};

std::string Shape::NAME = "Shape";

std::ostream &operator<<(std::ostream &os, Shape const& m) {
	return os << ANSI::YELLOW << Shape::NAME << "{" << m.t << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Shape const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Shape::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

