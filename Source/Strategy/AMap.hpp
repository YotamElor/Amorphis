#pragma once
#include <BWAPI.h>
#include "Plan.hpp"

#include "bwem/map.h"
#include "bwem/area.h"


namespace Amorphis {


	class AMap {
		BWEM::Area const *m_mainBaseArea = NULL;
		BWEM::Area const *m_naturalArea = NULL;
	public:

		AMap();
		void init();
		void onFrame();
		void draw() const;
		BWAPI::TilePosition nextExpansionPosition() const;
	};


}