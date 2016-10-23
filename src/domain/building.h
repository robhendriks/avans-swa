#pragma once
#include "base_placeable_object.h"

namespace domain {
	class building :
			public base_placable_object {
	public:
		building();
		int getHitPoints();
		void setHitPoints(const int hitPoints);
        int getRegenPerSec();
        void setRegenPerSec(const int regenPerSec);
		~building();

	private:
		int _hitPoints;
		int _regenPerSec;
	};
}