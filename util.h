#pragma once
#include <cstdlib>

float rf(int min, int max) {
	if (min == max) {
		return (float)min;
	}
	return (float)(min + (rand() % abs(max - min)));
}

glm::vec2 normOrZero(glm::vec2 v) {
	return v.x == 0 && v.y == 0 ? v : glm::normalize(v);
}
