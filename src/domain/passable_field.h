#pragma once
#include "base_placeable_object.h"
namespace domain {
	class passable_field {
	public:
		passable_field();
		
		~passable_field();

	private:
		base_placable_object _placedObject;
	};
}
