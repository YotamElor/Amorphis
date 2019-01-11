#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace BWAPI;
using namespace BWAPI::UnitTypes;
using namespace std;


namespace Amorphis {


	Strategy::Strategy()
	{
		// initial units
		m_buildOrder.push_back(make_pair(Zerg_Drone, 4));
		m_buildOrder.push_back(make_pair(Zerg_Overlord, 1));
		// build order
		m_buildOrder.push_back(make_pair(Zerg_Drone, 5));
		m_buildOrder.push_back(make_pair(Zerg_Overlord, 1));
		m_buildOrder.push_back(make_pair(Zerg_Spawning_Pool, 1));
		m_buildOrder.push_back(make_pair(Zerg_Extractor, 1));
		m_buildOrder.push_back(make_pair(Zerg_Drone, 1));
		m_buildOrder.push_back(make_pair(Zerg_Zergling, 6));
	}


	void Strategy::onFrame()
	{
		m_nextToBuild = None;
		std::map<BWAPI::UnitType, int> requiredUnitCount;
		for (int i = 0; i < (int)m_buildOrder.size(); i++) {
			if (requiredUnitCount.count(m_buildOrder[i].first) == 0) {
				requiredUnitCount[m_buildOrder[i].first] = m_buildOrder[i].second;
			}
			else {
				requiredUnitCount[m_buildOrder[i].first] += m_buildOrder[i].second;
			}
			if (UM->unitsCounter().getCounter(m_buildOrder[i].first) < requiredUnitCount[m_buildOrder[i].first]) {
				m_nextToBuild = m_buildOrder[i].first;
				break;
			}
		}
	}


	void Strategy::draw() const
	{
		string s = string("next: ") + string(m_nextToBuild != NULL ? m_nextToBuild.toString() : "NONE");
		Broodwar->drawTextScreen(Position(0,20), s.c_str());
	}


}