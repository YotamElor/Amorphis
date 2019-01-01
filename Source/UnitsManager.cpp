#include "UnitsManager.hpp"

namespace Amorphis {

	UnitsManager::UnitsManager()
	{
		m_unitSet = AUnitSet("dragoons", UnitTypes::Enum::Protoss_Dragoon);
	}

	void UnitsManager::onUnitDiscover(BWAPI::Unit unit) {
		if (unit->getPlayer()->getID() != Broodwar->self()->getID()) {
			return;
		}
		Broodwar->sendText("UnitsManager::onUnitDiscover %s", unit->getType().c_str());
		if (unit->getType() == UnitTypes::Enum::Protoss_Dragoon) {
			RangedUnit* rangedUnit = new RangedUnit(unit);
			m_unitSet.insert(rangedUnit);
		}
	}


	void UnitsManager::draw()
	{
		m_unitSet.displayUnitNames();
	}


}
