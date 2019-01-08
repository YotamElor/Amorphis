#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void Strategy::onFrame()
	{
		// TODO: count units loaded into other units. see reference of Broodwar->self()->getUnits()
		m_unitsCounter.clear();
		for (const Unit &u : Broodwar->self()->getUnits()) {
			UnitType unitType = u->getType();
			if (u->getType() == UnitTypes::Zerg_Egg) {
				unitType = u->getLastCommand().getUnitType();
			}
			if (m_unitsCounter.find(unitType) == m_unitsCounter.end()) {
				m_unitsCounter[unitType] = 0;
			}
			m_unitsCounter[unitType]++;
		}
		if (m_unitsCounter[UnitTypes::Zerg_Drone] == 8 && m_unitsCounter[UnitTypes::Zerg_Overlord] == 1) {
			m_nextToBuild = UnitTypes::Zerg_Overlord;
		}
		else {
			m_nextToBuild = UnitTypes::Zerg_Drone;
		}
	}


	void Strategy::draw() const
	{
		string s = "";
		for (auto it = m_unitsCounter.begin(); it != m_unitsCounter.end(); it++) {
			s += it->first.toString() + string(" (") + to_string(it->second) + string(")\n");
		}
		if (m_nextToBuild != NULL) {
			s += string("next: ") + m_nextToBuild.toString();
		}
		Broodwar->drawTextScreen(Position(0,20), s.c_str());
	}


}