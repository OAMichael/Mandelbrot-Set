#pragma once

#include "../Headers/Iterations.hpp"

namespace MSet {

	class Fractal {

	private:
		const char* name;
	
	public:
		Fractal(const char* name_);
		void show();
	};
}