#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"
#include "Plan.hpp"


using namespace BWAPI;
using namespace BWAPI::UnitTypes;
using namespace std;


namespace Amorphis {


	const char * PlanTrigger::toString(PlanTriggerType type) const
	{
		switch (type)
		{
		case NotSet: return "NotSet"; break;
		case UnitsHaveLessThan: return "UnitsHaveLessThan"; break;
		case FreeSupplyLessThan: return "FreeSupplyLessThan"; break;
		}
		AERR(string("Error convert PlanTriggerType to string") + to_string(type));
		return "";
	}


	bool PlanTrigger::check() const
	{
		if (m_type == UnitsHaveLessThan) {
			return UM->unitsCounter().getCounter(m_unitType) < m_number;
		}
		else if (m_type == FreeSupplyLessThan) {
			return Broodwar->self()->supplyTotal() - Broodwar->self()->supplyUsed() < m_number;
		}
		else {
			AERR("PlanTrigger::check() type error");
		}
		return false;
	}

	std::string PlanTrigger::toString() const
	{
		return string("(") + toString(m_type) + string(",") + m_unitType.toString() + string(",") + to_string(m_number) + string(")");
	}


	std::string PlanAction::toString() const
	{
		return string("(") + toString(m_type) + string(",") + m_unitType.toString() + string(")");
	}


	const char * PlanAction::toString(PlanActionType type) const
	{
		switch (type)
		{
		case NotSet: return "NotSet"; break;
		case BuildUnit: return "BuildUnit"; break;
		}
		AERR(string("Error convert PlanActionType to string") + to_string(type));
		return "";
	}

}