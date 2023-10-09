#pragma once

#include <iostream>
#include <string>

class GLLoadException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Failed to load OpenGL";
	}
};