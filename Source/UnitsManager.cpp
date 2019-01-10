#include "UnitsManager.hpp"
#include "Utils/Logger.hpp"


using namespace std;


namespace Amorphis {


	UnitsManager* UnitsManager::m_instance = NULL;


	UnitsManager* UnitsManager::getInstance()
	{
		if (m_instance == NULL) {
			m_instance = new UnitsManager();
		}
		return m_instance;
	}


	void UnitsManager::init()
	{
	}


	void UnitsManager::addUnit(BWAPI::Unit unit) {
		if (m_knownUnitIDs.count(unit->getID())==0) {
			m_knownUnitIDs[unit->getID()] = 1;
			AUnit* aUnit = new AUnit(unit);
			m_allUnits.insert(aUnit);
		}
	}


	void UnitsManager::onFrame()
	{
		m_unitsCounter.clear();
		for (auto it = m_allUnits.begin(); it != m_allUnits.end(); ) {
			if (!(*it)->isAlive()) {
				it = m_allUnits.erase(it);
			}
			else {
				m_unitsCounter.addUnit((*it)->getType());
				it++;
			}
		}
	}


	void UnitsManager::draw()
	{
		m_unitsCounter.draw();
	}


}
