#pragma once

#include <iostream>

#include "../module/ecs/ansi.h"

struct Size {
	double size;
	static std::string NAME;
};

std::string Size::NAME = "Size";

std::ostream &operator<<(std::ostream &os, Size const& m) {
	return os << ANSI::YELLOW << Size::NAME << "{" << m.size << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Size const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Size::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

