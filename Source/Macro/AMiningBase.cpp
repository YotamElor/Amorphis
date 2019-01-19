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


	AMiningBase::AMiningBase(const std::string &name, BWAPI::Unit resourceDepot) : m_name(name)
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
		m_drawPositionTL = Position(m_resourceDepot->getTilePosition()) + Position(55, 35);
		m_drawPositionBR = m_drawPositionTL + Position(40, 40);
		m_textPosition = m_drawPositionTL + Position(2, 0);

		BWAPI::UnitType type;
		if (Broodwar->self()->getRace() == Races::Protoss) {
			type = UnitTypes::Enum::Protoss_Probe;
		} else if (Broodwar->self()->getRace() == Races::Terran) {
			type = UnitTypes::Enum::Terran_SCV;
		} else {
			type = UnitTypes::Enum::Zerg_Drone;
		}
		m_workers = new WorkerUnitSet(m_name, type);
		m_workers->gather(this, 0);
		UM->addUnitSet(m_workers);

		for (const Mineral *m : m_baseBwem->Minerals()) {
			m_minerals.push_back( AMineralPatch(m->Unit(), m_resourceDepot->getDistance(m->Unit())) );
		}
		sort(m_minerals.begin(), m_minerals.end(), &AMineralPatchCmp);

		for (const Geyser *g : m_baseBwem->Geysers()) {
			m_gasGysers.push_back(g->Unit());
		}
	}


	void AMiningBase::draw() const
	{
		if (DisplaySettings::UnitName) {
			Broodwar->drawBoxMap(m_drawPositionTL, m_drawPositionBR, Color(50, 50, 50), true);
			Broodwar->drawBoxMap(m_drawPositionTL, m_drawPositionBR, Color(200, 200, 200), false);
			Broodwar->drawTextMap(m_textPosition, "M : %d\nG : %d\nL : %d", m_workers->size() - m_workers->numGasWorkers(), m_workers->numGasWorkers(), m_resourceDepot->getLarva().size());
			for (const AMineralPatch &m : m_minerals) {
				m.draw();
			}
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


	bool AMiningBase::build(BWAPI::UnitType whatToBuild, BWAPI::TilePosition tilePosition)
	{
		const TilePosition buildTile = (tilePosition.x == 0 && tilePosition.y == 0)
			? Broodwar->getBuildLocation(whatToBuild, m_resourceDepot->getTilePosition())
			: Broodwar->getBuildLocation(whatToBuild, tilePosition);
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
			//AWARN("morphLarva: larva.size() == 0");
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