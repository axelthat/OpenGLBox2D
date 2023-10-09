#pragma once

#include <iostream>
#include <string>

class WindowCreationException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Failed to create Window";
	}
};