#pragma once
#include "base_placable_object.h"

namespace domain {
	class building :
			public base_placable_object {
	public:
		building();

		~building();
	};
}