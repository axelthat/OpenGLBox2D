#include <fstream>
#include <sstream>

#include "Util.h"

float Util::PIXELS_PER_METER = 30.0f;

std::string Util::ReadFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("File \"" + path + "\" not found!");
	}

	std::stringstream stream;
	stream << file.rdbuf();

	auto contents = stream.str();

	file.close();

	return contents;
}

float Util::PixelToMeter(float pixels) {
	return pixels / PIXELS_PER_METER;
}

float Util::MeterToPixel(float meters) {
	return meters * PIXELS_PER_METER;
}