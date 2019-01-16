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

			bool hasFinisedRefinery = false;
			for (auto g : m_miningBase->gysers()) {
				if (g->getType() != UnitTypes::Resource_Vespene_Geyser) {
					hasFinisedRefinery = true;
				}
			}
			if (hasFinisedRefinery) {
				int numGasWorkers = 0;
				for (AUnit *unit : m_units) {
					numGasWorkers += unit->state() == AUnit::GatherGas;
				}
				while (numGasWorkers > m_numGasWorkers) {
					for (AUnit *unit : m_units) {
						if (unit->state() == AUnit::GatherGas) {
							unit->stop();
							numGasWorkers--;
							Broodwar->sendText("gas worker removed, num gas workers: %d / %d", numGasWorkers, m_numGasWorkers);
							break;
						}
					}
				}
				while (numGasWorkers < m_numGasWorkers) {
					for (AUnit *unit : m_units) {
						if (unit->state() != AUnit::GatherGas) {
							unit->gather(m_miningBase->gysers()[0]);
							numGasWorkers++;
							Broodwar->sendText("gas worker added %d, num gas workers: %d / %d", unit->unit()->getID(), numGasWorkers, m_numGasWorkers);
							break;
						}
					}
				}
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