#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H
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
#endif //CITY_DEFENCE_GAME_WORLD_H
