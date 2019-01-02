#pragma once
#include <BWAPI.h>
#include <set>
#include "Micro/RangedUnitSet.hpp"
#include "Micro/RangedUnit.hpp"
#include "Micro/EnemyUnitSet.hpp"


using namespace BWAPI;


namespace Amorphis {


	class UnitsManager{
		RangedUnitSet m_unitSet;
		EnemyUnitSet m_enemyUnits;
	public:
		UnitsManager();
		void onUnitDiscover(BWAPI::Unit unit);
		void onFrame();
		void draw();
	};


}