#include "UnitsManager.hpp"

namespace Amorphis {

	UnitsManager::UnitsManager()
	{
		m_unitSet = RangedUnitSet("Dragoons", UnitTypes::Enum::Protoss_Dragoon);
		m_unitSet.setDrawPosition(Position(5, 20));
	}

	void UnitsManager::onUnitDiscover(BWAPI::Unit unit) {
		if (unit->getPlayer()->getID() == Broodwar->self()->getID()) {
			if (unit->getType() == UnitTypes::Enum::Protoss_Dragoon) {
				RangedUnit* rangedUnit = new RangedUnit(unit);
				m_unitSet.insert(rangedUnit);
			}
		}
		else if (unit->getPlayer()->getID() == Broodwar->enemy()->getID())
		{
			m_enemyUnits.insert(unit);
		}
	}


	void UnitsManager::onFrame()
	{
		if (m_unitSet.state() != RangedUnitSet::State::Attack && m_enemyUnits.size() > 0) {
			m_unitSet.setEnemy(&m_enemyUnits);
		}
		m_unitSet.onFrame();
		m_enemyUnits.removeDead();
	}

	void UnitsManager::draw()
	{
		m_unitSet.draw();
	}


}
