#pragma once
#include <BWAPI.h>
#include "Plan.hpp"

#include "bwem/map.h"
#include "AArea.hpp"


namespace Amorphis {


	class AMap {
		static AMap* m_instance;
		AArea const *m_mainBaseArea = NULL;
		AArea const *m_naturalArea = NULL;
		std::map<int, AArea> m_areas;
	public:
		AMap() {}
		static AMap* getInstance();
		void init();
		void onFrame();
		void draw() const;
		BWAPI::TilePosition nextExpansionPosition() const;
	};


#define MAP AMap::getInstance()

}