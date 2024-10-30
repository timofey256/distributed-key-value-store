#pragma once
#include "utils.h"

template <class T>
void print_set(std::set<T> v) {
	for (auto& x : v) {
		std::cout << x << std::endl;
	}
};