#include "Scouting.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	void Scouting::init()
	{
		for (TilePosition t : theMap.StartingLocations())
		{
			if (t != Broodwar->self()->getStartLocation()) {
				m_enemyPossibleStartLocations.push_back(t);
			}
		}
		Broodwar->sendText("m_enemyPossibleStartLocations.size() = %d", m_enemyPossibleStartLocations.size());
		m_overlordFirst = new OverlordUnitSet("OV first", UnitTypes::Zerg_Overlord);
		UM->addUnitSet(m_overlordFirst);
		m_overlordSecond = new OverlordUnitSet("OV second", UnitTypes::Zerg_Overlord);
		UM->addUnitSet(m_overlordSecond);
	}


	void Scouting::onFrame()
	{
		if (m_overlordFirst->size() == 0) {
			UnitSetUnitPair p = UM->getAvailableUnit(UnitTypes::Zerg_Overlord, UnitTypes::None, "None");
			if (p.first != NULL) {
				UM->moveUnit(p, m_overlordFirst);
				m_overlordFirst->move(Position(m_enemyPossibleStartLocations[0]));
			}
		}
		if (m_overlordSecond->size() == 0) {
			UnitSetUnitPair p = UM->getAvailableUnit(UnitTypes::Zerg_Overlord, UnitTypes::None, "None");
			if (p.first != NULL) {
				UM->moveUnit(p, m_overlordSecond);
				m_overlordSecond->move(Position(MAP->nextExpansionPosition()));
			}
		}
	}


}