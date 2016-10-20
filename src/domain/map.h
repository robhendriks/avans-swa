#pragma once
#include "base_map.h"
#include "base_field.h";
#include <vector>;
namespace domain {
	class map :
			public base_map {
	public:
		map();

		~map();

	private:
		std::vector<base_field> _fields;
	};
}
