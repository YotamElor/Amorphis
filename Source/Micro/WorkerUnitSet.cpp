#include "WorkerUnitSet.hpp"
#include "Utils/Geometry.hpp"
#include "WorkerUnit.hpp"
#include "Macro/AMiningBase.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void WorkerUnitSet::onFrame_()
	{
		if (m_state == Gather) {
			if (m_miningBase == NULL) {
				AERR("m_miningBase == NULL");
			}

			for (AUnit *unit : m_units) {
				if (unit->state() == AUnit::Idle) {
					unit->gather(m_miningBase->getNextMineralPatch());
				}
			}
		}
		for (AUnit *unit : m_units) {
			unit->onFrame();
		}
	}


	void WorkerUnitSet::draw() const
	{
		AUnitSet::draw();
		if (DisplaySettings::AUnitSetBox) {
			Broodwar->drawTextScreen(m_textPosition, "\n%s", toString(m_state));
		}
	}


	void WorkerUnitSet::gather(AMiningBase* miningBase, const int numGasWorkers)
	{
		m_miningBase = miningBase;
		m_numGasWorkers = numGasWorkers;
		m_state = Gather;
	}


	void WorkerUnitSet::build(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition)
	{
		m_units[0]->build(unitType, tilePosition);
	}


}