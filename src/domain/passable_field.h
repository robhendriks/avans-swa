#ifndef CITY_DEFENCE_PASSABLE_FIELD_H
#define CITY_DEFENCE_PASSABLE_FIELD_H

#include "base_placeable_object.h"

namespace domain {
	class passable_field {
	public:
		passable_field();
		
		~passable_field();

	private:
		base_placeable_object _placed_object;
	};
}
#endif //CITY_DEFENCE_PASSABLE_FIELD_H
