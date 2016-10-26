#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H
#include "base_placeable_object.h"

namespace domain {
	class building :
			public base_placeable_object {
	public:
		building();
		int get_hit_points();
		void set_hit_points(int hit_points);
        int get_regen_per_sec();
        void set_regen_per_sec(int regen_per_sec);
		~building();

	private:
		int _hit_points;
		int _regen_per_sec;
	};
}
#endif //CITY_DEFENCE_BUILDING_H
