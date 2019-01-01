#pragma once
#include <BWAPI.h>
#include <set>
#include "Micro/AUnitSet.hpp"
#include "Micro/RangedUnit.hpp"


using namespace BWAPI;


namespace Amorphis {


	class UnitsManager{
		AUnitSet m_unitSet;
	public:
		UnitsManager();
		void onUnitDiscover(BWAPI::Unit unit);
		void draw();
	};


}