#include "WorkerUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	WorkerUnit::WorkerUnit(BWAPI::Unit unit) : AUnit(unit)
	{
	}


	void WorkerUnit::gather(BWEM::Ressource const * resource)
	{
		m_targetUnit = resource->Unit();
		if (resource->IsMineral()) {
			m_state = GatherMinerals;
		} else if (resource->IsGeyser()) {
			m_state = GatherGas;
		} else {
			AERR("resource problem");
		}
	}


	void WorkerUnit::onFrame_()
	{
		if (m_state == GatherMinerals) {
			if (m_unit->isIdle()) {
				m_unit->gather(m_targetUnit);
			}
		}
	}

}