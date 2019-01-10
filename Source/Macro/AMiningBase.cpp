#include "AMiningBase.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "Micro/WorkerUnit.hpp"
#include "UnitsManager.hpp"


#include "bwem/map.h"
#include "bwem/area.h"
#include "bwem/neutral.h"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	AMiningBase::AMiningBase(const std::string &name, BWAPI::Unit resourceDepot) : m_name(name), m_numGasWorkers(0)
	{
		m_resourceDepot = resourceDepot;

		for (const Area & area : theMap.Areas()) {
			for (const Base & base : area.Bases()) {
				if (m_resourceDepot->getTilePosition() ==  base.Location()) {
					m_baseBwem = &base;
				}
			}
		}
		if (m_baseBwem == NULL) {
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
		m_workers->gather(this, m_numGasWorkers);
		UM->addUnitSet(m_workers);

		for (const Mineral *m : m_baseBwem->Minerals()) {
			m_minerals.push_back( AMineralPatch(m->Unit(), m_resourceDepot->getDistance(m->Unit())) );
		}
		sort(m_minerals.begin(), m_minerals.end(), &AMineralPatchCmp);
	}


	void AMiningBase::draw() const
	{
		Broodwar->drawBoxMap(Position(m_resourceDepot->getTilePosition()), Position(m_resourceDepot->getTilePosition() + m_resourceDepot->getType().tileSize()), Color(200, 200, 200));
		for (const AMineralPatch &m : m_minerals) {
			m.draw();
		}
	}


	BWAPI::Unit AMiningBase::getNextMineralPatch()
	{
		vector<int> desiredWorkersOnPatches(m_minerals.size());
		vector< vector<AUnit*> > unitsOnPatches(m_minerals.size());
		for (AMineralPatch &m : m_minerals) {
			m.resetNumWorkers();
		}
		for (AUnit* a : m_workers->units()) {
			const BWAPI::Unit t = a->targetUnit();
			for (int mIdx = 0; mIdx < (int)m_minerals.size(); mIdx++) {
				AMineralPatch &m = m_minerals[mIdx];
				if (t != NULL && t->getID() == m.unit()->getID()) {
					m.addWorker();
					unitsOnPatches[mIdx].push_back(a);
				}
			}
		}
		for (int i = 0; i < (int)unitsOnPatches.size(); i++) {
			if (unitsOnPatches[i].size() > 3) {
				for (int j = 3; j < (int)unitsOnPatches[i].size(); j++) {
					unitsOnPatches[i][j]->stop();
				}
			}
		}
		for (int maxNumWorkers = 0; maxNumWorkers < 3; maxNumWorkers++) {
			for (const AMineralPatch &m : m_minerals) {
				if (m.numWorkers() <= maxNumWorkers) {
					return m.unit();
				}
			}
		}
		return m_minerals[0].unit();
	}


	bool AMiningBase::build(BWAPI::UnitType whatToBuild)
	{
		const TilePosition buildTile = Broodwar->getBuildLocation(whatToBuild, m_resourceDepot->getTilePosition());
		m_workers->build(whatToBuild, buildTile);
		return false;
	}


	bool AMiningBase::morphLarva(BWAPI::UnitType whatToBuild)
	{
		if (whatToBuild.isBuilding()) {
			AERR("morphLarva: whatToBuild.isBuilding()");
		}
		BWAPI::Unitset larva = m_resourceDepot->getLarva();
		if (larva.size() == 0) {
			AWARN("morphLarva: larva.size() == 0");
			return false;
		}
		else {
			(*larva.begin())->morph(whatToBuild);
		}
		return true;
	}

	void AMiningBase::onFrame()
	{
		if (Broodwar->getFrameCount()%20 == 0)
		{
			// in order to update statistics
			getNextMineralPatch();
		}
		for (auto it = m_minerals.begin(); it != m_minerals.end(); ) {
			if (!it->unit()->exists()) {
				m_minerals.erase(it);
				getNextMineralPatch();
			}
			else {
				it++;
			}
		}
	}


}