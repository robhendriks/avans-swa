#pragma once
#include "base_placeable_object.h"

namespace domain {
	class building :
			public base_placable_object {
	public:
		building();
		int get_hit_points();
		void set_hit_points(const int hit_points);
        int get_regen_per_sec();
        void set_regen_per_sec(const int regen_per_sec);
		~building();

	private:
		int _hit_points;
		int _regen_per_sec;
	};
}