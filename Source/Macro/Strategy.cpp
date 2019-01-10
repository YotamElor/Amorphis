#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void Strategy::onFrame()
	{
		if (UM->unitsCounter().getCounter(UnitTypes::Zerg_Drone) > 8) {
			if (UM->unitsCounter().getCounter(UnitTypes::Zerg_Spawning_Pool) == 0) {
				m_nextToBuild = UnitTypes::Zerg_Spawning_Pool;
			}
			else {
				m_nextToBuild = UnitTypes::Zerg_Zergling;
			}
		}
		else if (UM->unitsCounter().getCounter(UnitTypes::Zerg_Drone) == 8 && UM->unitsCounter().getCounter(UnitTypes::Zerg_Overlord) == 1) {
			m_nextToBuild = UnitTypes::Zerg_Overlord;
		} 
		else {
			m_nextToBuild = UnitTypes::Zerg_Drone;
		}
	}


	void Strategy::draw() const
	{
		string s = string("next: ") + string(m_nextToBuild != NULL ? m_nextToBuild.toString() : "NONE");
		Broodwar->drawTextScreen(Position(0,20), s.c_str());
	}


}