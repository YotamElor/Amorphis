#pragma once
#include <BWAPI.h>
#include "AMap.hpp"
#include "Micro/OverlordUnitSet.hpp"


namespace Amorphis {


	class Scouting {
		std::vector<BWAPI::TilePosition> m_enemyPossibleStartLocations;
		OverlordUnitSet *m_overlordFirst, *m_overlordSecond;
	public:
		void init();
		void onFrame();
	};


}