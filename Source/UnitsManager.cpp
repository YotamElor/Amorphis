#include "UnitsManager.hpp"
#include "Utils/Logger.hpp"
#include "Micro/WorkerUnit.hpp"


using namespace std;
using namespace BWAPI;
using namespace BWAPI::UnitTypes;


namespace Amorphis {


	UnitsManager* UnitsManager::m_instance = NULL;


	UnitsManager* UnitsManager::getInstance()
	{
		if (m_instance == NULL) {
			m_instance = new UnitsManager();
		}
		return m_instance;
	}


	void UnitsManager::init()
	{
		if (m_initialized) {
			return;
		}
		m_initialized = true;
		addUnitSet(new AUnitSet("None", None));

		if (Broodwar->self()->getRace() == Races::Zerg) {
			m_workerType = Zerg_Drone;
		}
		else if (Broodwar->self()->getRace() == Races::Protoss) {
			m_workerType = Protoss_Probe;
		}
		else if (Broodwar->self()->getRace() == Races::Terran) {
			m_workerType = Terran_SCV;
		}
	}


	void UnitsManager::addUnit(BWAPI::Unit unit) {
		if (!m_initialized) {
			init();
		}
		if (m_knownUnitIDs.count(unit->getID())==0) {
			m_knownUnitIDs[unit->getID()] = 1;
			AUnit* aUnit;
			if (unit->getType().isWorker()) {
				aUnit = new WorkerUnit(unit);
			}
			else if (unit->getType().isBuilding()) {
				aUnit = new AUnit(unit);
			}
			else {
				aUnit = new AUnit(unit);
			}
			m_allUnits.insert(aUnit);
			(*m_unitSets[None].begin())->addUnit(aUnit);
		}
	}


	void UnitsManager::removeUnit(BWAPI::Unit unit)
	{
		for (auto itMap = m_unitSets.begin(); itMap != m_unitSets.end(); itMap++) {
			for (auto itSet = itMap->second.begin(); itSet != itMap->second.end(); itSet++) {
				(*itSet)->removeUnit(unit);
			}
		}
		for (auto it = m_allUnits.begin(); it != m_allUnits.end(); it++) {
			if ((*it)->unit() == unit) {
				m_knownUnitIDs.erase((*it)->unit()->getID());
				delete *it;
				it = m_allUnits.erase(it);
				break;
			}
		}
	}

	void UnitsManager::addUnitSet(AUnitSet* unitSet)
	{
		if (m_unitSets.count(unitSet->type()) == 0) {
			m_unitSets[unitSet->type()] = set<AUnitSet*>();
		}
		m_unitSets[unitSet->type()].insert(unitSet);
		setUnitSetsDrawPosition();
	}


	void UnitsManager::setUnitSetsDrawPosition()
	{
		const Position startPos(280, 2);
		int i = 0;
		for (auto itMap = m_unitSets.begin(); itMap != m_unitSets.end(); itMap++) {
			for (auto itSet = itMap->second.begin(); itSet != itMap->second.end(); itSet++) {
				(*itSet)->setDrawPosition(startPos + Position(0,i*32));
				i++;
			}
		}
	}


	void UnitsManager::onFrame()
	{
		for (auto itMap = m_unitSets.begin(); itMap != m_unitSets.end(); itMap++) {
			for (auto itSet = itMap->second.begin(); itSet != itMap->second.end(); itSet++) {
				(*itSet)->onFrame();
			}
		}

		// TODO: count units loaded into other units. see reference of Broodwar->self()->getUnits()
		m_unitsCounter.clear();
		m_finishedUnitsCounter.clear();
		m_availableMinerals = Broodwar->self()->minerals();
		m_availableGas = Broodwar->self()->gas();
		for (auto it = m_allUnits.begin(); it != m_allUnits.end(); ) {
			if (!(*it)->isAlive()) {
				m_knownUnitIDs.erase((*it)->unit()->getID());
				delete *it;
				it = m_allUnits.erase(it);
			}
			else {
				m_finishedUnitsCounter.addUnit((*it)->getType());
				m_unitsCounter.addKey((*it)->getType());
				m_unitsCounter.addUnit((*it)->getFinalType());
				m_availableMinerals -= (*it)->mineralDebt();
				m_availableGas -= (*it)->gasDebt();
				it++;
			}

			UnitSetUnitPair workerToMove = getAvailableUnit(m_workerType, None, "None");
			if (workerToMove.first != NULL && m_unitSets.count(m_workerType)>0 && m_unitSets[m_workerType].size() > 0) {
				moveUnit(workerToMove, *m_unitSets[m_workerType].begin());
			}
		}
	}


	UnitSetUnitPair UnitsManager::getAvailableUnit(BWAPI::UnitType unitType, BWAPI::UnitType setType, const std::string &setName)
	{
		if (m_unitSets.count(setType) == 0 || m_unitSets[setType].size() == 0) {
			return UnitSetUnitPair(NULL, NULL);
		}
		for (auto itUnitSet = m_unitSets[setType].begin(); itUnitSet != m_unitSets[setType].end(); itUnitSet++) {
			if ((*itUnitSet)->name() == setName) {
				for (auto itUnit = (*itUnitSet)->units().begin(); itUnit != (*itUnitSet)->units().end(); itUnit++) {
					if ((*itUnit)->getType() == unitType) {
						return UnitSetUnitPair(*itUnitSet,*itUnit);
					}
				}
			}
		}
		return UnitSetUnitPair(NULL,NULL);
	}


	void UnitsManager::moveUnit(UnitSetUnitPair s, AUnitSet* d) const
	{
		s.first->removeUnit(s.second);
		d->addUnit(s.second);
		if (LogSettings::LogUnitSetMove) {
			ALOG(string("Moving ") + s.second->getType().c_str() + string(" from ") + s.first->name() + string("(") + to_string(s.first->size()) + string(") to ") + d->name() + string("(") + to_string(d->size()) + string(")"));
		}
	}


	void UnitsManager::draw()
	{
		if (DisplaySettings::UnitsManager) {
			string s = string("m=") + to_string(m_availableMinerals) + string(" g=") + to_string(m_availableGas);
			Broodwar->drawTextScreen(Position(0, 20), +s.c_str());
			m_unitsCounter.draw(m_finishedUnitsCounter);
			for (auto itMap = m_unitSets.begin(); itMap != m_unitSets.end(); itMap++) {
				for (auto itSet = itMap->second.begin(); itSet != itMap->second.end(); itSet++) {
					(*itSet)->draw();
				}
			}
			for (auto it = m_allUnits.begin(); it != m_allUnits.end(); it++) {
				(*it)->draw();
			}
		}
	}


}
