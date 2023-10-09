#pragma once

#include <iostream>
#include <string>

class ShaderLoadException : public std::exception {
private:
	const std::string reason;

public:
	ShaderLoadException(const std::string& reason) : reason("Failed to load shader: " + reason) {};

public:
	const char* what() const noexcept override {
		return reason.c_str();
	}
};