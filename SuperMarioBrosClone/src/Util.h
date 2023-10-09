#pragma once

#include <string>
#include <random>

class Util {
private:
	static float PIXELS_PER_METER;

public:
	static std::string ReadFile(const std::string& path);

	static float PixelToMeter(float pixels);
	static float MeterToPixel(float meters);

	template <typename T>
	static T GetRandomNumber(T min, T max) {
		std::random_device rd;
		std::mt19937 rng(rd());

		if constexpr (std::is_integral<T>::value) {
			std::uniform_int_distribution<T> uni(min, max);
			return uni(rng);
		}
		else if constexpr (std::is_floating_point<T>::value) {
			std::uniform_real_distribution<T> uni(min, max);
			return uni(rng);
		}

		return min;
	};
};