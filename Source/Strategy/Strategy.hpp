#pragma once
#include <BWAPI.h>
#include "Plan.hpp"
#include "Scouting.hpp"


namespace Amorphis {


	class Strategy {
		PlanAction m_nextAction;
		std::vector< std::pair<BWAPI::UnitType, int> > m_buildOrder;
		planType m_plan, m_activePlan;
		Scouting m_scouting;
	public:
		Strategy();
		void onFrame();
		void init();
		const PlanAction& nextAction() const { return m_nextAction;  }
		void draw() const;
	};


}