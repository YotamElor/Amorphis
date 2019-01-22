#pragma once
#include <BWAPI.h>

#include "bwem/map.h"
#include "bwem/area.h"


namespace Amorphis {


	class EnemyBuilding {
		BWAPI::Unit m_unit;
		int m_lastScoutingFrame;
	public:
		EnemyBuilding(BWAPI::Unit unit);
	};


}