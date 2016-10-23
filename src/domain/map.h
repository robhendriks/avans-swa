#pragma once
#include "base_map.h"
#include "base_field.h"
#include "passable_field.h
#include <vector>
namespace domain {
	class map :
			public base_map {
	public:
		map();
		~map();

	private:
		std::vector<base_field> _fields;
		std::vector<passable_field> _placedBuildingFields;
	};
}
