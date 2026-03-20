#include "Some.h"

#include <iostream>

void fun(const Some& a) {
	std::cout << "fun:" << std::endl;
	auto b = a.Do(0);
}

void fun2(Some a) {
	std::cout << "fun2:" << std::endl;
	auto b = a.Do(0);
}

int main() {
	Some a;
	fun(a);
	fun2(a);
	return 0;
}