#include "UnitsManager.hpp"
#include "Utils/Logger.hpp"
#include "Micro/WorkerUnit.hpp"


using namespace std;


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
		addUnitSet(new AUnitSet("None", UnitTypes::None));
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
			(*m_unitSets[UnitTypes::None].begin())->addUnit(aUnit);
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
		const Position startPos(100, 2);
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
		m_mineralDebt = 0;
		m_gasDebt = 0;
		for (auto it = m_allUnits.begin(); it != m_allUnits.end(); ) {
			if (!(*it)->isAlive()) {
				m_knownUnitIDs.erase((*it)->unit()->getID());
				delete *it;
				it = m_allUnits.erase(it);
			}
			else {
				m_unitsCounter.addUnit((*it)->getFinalType());
				m_mineralDebt += (*it)->mineralDebt();
				m_gasDebt += (*it)->gasDebt();
				it++;
			}

			vector<AUnit*> workersToMove;
			for (auto it = (*m_unitSets[UnitTypes::None].begin())->units().begin(); it != (*m_unitSets[UnitTypes::None].begin())->units().end(); it++) {
				if ((*it)->getType().isWorker() && m_unitSets.count((*it)->getType()) > 0 && m_unitSets[(*it)->getType()].size() > 0) {
					if (m_unitSets[(*it)->getType()].size() != 1) {
						AERR("m_unitSets[(*it)->getType()].size() != 1 for workers");
					}
					workersToMove.push_back(*it);
				}
			}
			for (int i = 0; i < (int)workersToMove.size(); i++) {
				moveUnit(*m_unitSets[UnitTypes::None].begin(), *m_unitSets[workersToMove[i]->getType()].begin(), workersToMove[i]);
			}
		}
	}


	void UnitsManager::moveUnit(AUnitSet* s, AUnitSet* d, AUnit* u) const
	{
		s->removeUnit(u);
		d->addUnit(u);
	}


	void UnitsManager::draw()
	{
		string s = string("debt: m=") + to_string(m_mineralDebt) + string(" g=") + to_string(m_gasDebt);
		Broodwar->drawTextScreen(Position(0, 35),  + s.c_str());
		m_unitsCounter.draw();
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
