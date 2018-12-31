#pragma once
#include <BWAPI.h>
#include <set>
#include "Micro/AUnit.hpp"
#include "Micro/RangedUnit.hpp"


using namespace BWAPI;


namespace Amorphis {


	class UnitsManager{
		std::set<AUnit*> m_units;
	public:
		void onUnitDiscover(BWAPI::Unit unit);
		void draw();
	};


}