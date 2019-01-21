#pragma once
#include <BWAPI.h>
#include "Plan.hpp"

#include "bwem/map.h"
#include "AArea.hpp"


namespace Amorphis {


	class AMap {
		AArea const *m_mainBaseArea = NULL;
		AArea const *m_naturalArea = NULL;
		std::map<int, AArea> m_areas;
	public:

		AMap();
		void init();
		void onFrame();
		void draw() const;
		BWAPI::TilePosition nextExpansionPosition() const;
	};


}