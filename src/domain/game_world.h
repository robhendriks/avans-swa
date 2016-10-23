#pragma once
#include <vector>
#include "base_map.h"
namespace domain {
	class game_world {
	public:
		game_world();

		~game_world();

	private:
		std::vector<base_map> _map;
	};
}