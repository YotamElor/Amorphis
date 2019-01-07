#include "AMiningBase.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "Micro/WorkerUnit.hpp"

#include "bwem/map.h"
#include "bwem/area.h"
#include "bwem/neutral.h"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	AMiningBase::AMiningBase(const std::string &name, BWAPI::Unit resourceDepot) : m_name(name)
	{
		m_resourceDepot = resourceDepot;
		for (const Area & area : theMap.Areas()) {
			for (const Base & base : area.Bases()) {
				if (m_resourceDepot->getTilePosition() ==  base.Location()) {
					m_base = &base;
				}
			}
		}
		if (m_base == NULL) {
			AERR(string("m_base == NULL : ") + m_name);
		}

		BWAPI::UnitType type;
		if (Broodwar->self()->getRace() == Races::Protoss) {
			type = UnitTypes::Enum::Protoss_Probe;
		} else if (Broodwar->self()->getRace() == Races::Terran) {
			type = UnitTypes::Enum::Terran_SCV;
		} else {
			type = UnitTypes::Enum::Zerg_Drone;
		}
		m_workers = new WorkerUnitSet(m_name, type);
		m_workers->setDrawPosition(Position(205, 0));
	}


	void AMiningBase::draw() const
	{
		Broodwar->drawBoxMap(Position(m_resourceDepot->getTilePosition()), Position(m_resourceDepot->getTilePosition() + m_resourceDepot->getType().tileSize()), Color(200, 200, 200));
		for (const Mineral *m : m_base->Minerals()) {
			Broodwar->drawLineMap(m_base->Center(), m->Pos(), Color(50, 255, 50));
		}
		for (const Geyser *g : m_base->Geysers()) {
			Broodwar->drawLineMap(m_base->Center(), g->Pos(), Color(50, 255, 50));
		}
		m_workers->draw();
	}


	void AMiningBase::onFrame()
	{
		m_workers->onFrame();
	}


	void AMiningBase::addWorker(BWAPI::Unit unit)
	{
		m_workers->insert(new WorkerUnit(unit));
	}

	void AMiningBase::gather(int numGasWorkers) {
		m_workers->gather(this, numGasWorkers);
	}

}