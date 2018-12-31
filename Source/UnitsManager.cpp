#include "UnitsManager.hpp"

namespace Amorphis {


	void UnitsManager::onUnitDiscover(BWAPI::Unit unit) {
		if (unit->getPlayer()->getID() != Broodwar->self()->getID()) {
			return;
		}
		Broodwar->sendText("UnitsManager::onUnitDiscover %s", unit->getType().c_str());
		if (unit->getType() == UnitTypes::Enum::Protoss_Dragoon) {
			RangedUnit* rangedUnit = new RangedUnit(unit);
			m_units.insert(rangedUnit);
		}
	}


	void UnitsManager::draw()
	{
		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			(*it)->draw();
		}
	}


}
