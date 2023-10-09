#pragma once

#include <iostream>
#include <string>

class ShaderCompileException : public std::exception {
private:
	const std::string reason;

public:
	ShaderCompileException(const std::string& reason) : reason("Failed to compile shader: " + reason) {};

public:
	const char* what() const noexcept override {
		return reason.c_str();
	}
};