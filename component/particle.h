#pragma once

#include <glm/glm.hpp>

#include <iostream>

#include "../module/ecs/ansi.h"

enum class ParticleBehavior {
	Spiral, Straight,
};

struct Particle {
	ParticleBehavior behavior;
	float ttl;
	float clock;
	static std::string NAME;
};

std::string Particle::NAME = "Particle";

std::ostream &operator<<(std::ostream &os, Particle const& m) {
	return os << ANSI::YELLOW << Particle::NAME << "{" << m.ttl << " " << m.clock << "}" << ANSI::RESET;
}

std::ostream &operator<<(std::ostream &os, Particle const* m) {
	if (m == nullptr) {
		return os << ANSI::GRAY << Particle::NAME << "{INVALID}" << ANSI::RESET;
	}
	return os << *m;
}

