#pragma once

#include <iostream>
#include <string>

class WindowInitException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Failed to initialize window";
	}
};