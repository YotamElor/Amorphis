#pragma once
#include <BWAPI.h>
#include "Plan.hpp"


namespace Amorphis {


	class Strategy {
		BWAPI::UnitType m_nextToBuild = BWAPI::UnitTypes::None, m_lastBuilt = BWAPI::UnitTypes::None;
		std::vector< std::pair<BWAPI::UnitType, int> > m_buildOrder;
		planType m_plan, m_activePlan;
	public:
		Strategy();
		void onFrame();
		BWAPI::UnitType nextToBuild() const { return m_nextToBuild; }
		void draw() const;
	};


}