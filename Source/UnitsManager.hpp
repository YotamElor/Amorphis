#pragma once
#include <BWAPI.h>
#include <set>
#include "Micro/AUnit.hpp"
#include "Micro/AUnitSet.hpp"


using namespace BWAPI;


namespace Amorphis {


	class UnitsCounter {
		std::map<BWAPI::UnitType, int> m_map;
	public:
		UnitsCounter() {}
		void clear() {
			m_map.clear();
		}
		void addUnit(BWAPI::UnitType unitType) {
			if (m_map.find(unitType) == m_map.end()) {
				m_map[unitType] = 0;
			}
			m_map[unitType]++;
		}
		void addKey(BWAPI::UnitType unitType) {
			if (m_map.find(unitType) == m_map.end()) {
				m_map[unitType] = 0;
			}
		}
		int getCounter(BWAPI::UnitType unitType) const
		{
			if (m_map.find(unitType) == m_map.end()) {
				return 0;
			}
			return m_map.find(unitType)->second;
		}
		void draw(const UnitsCounter& secondCounter) const
		{
			std::string s = "";
			for (auto it = m_map.begin(); it != m_map.end(); it++) {
				if (it->second > 0) {
					s += it->first.toString() + std::string(" (") + std::to_string(secondCounter.getCounter(it->first)) + std::string("/") + std::to_string(it->second) + std::string(")\n");
				}
			}
			Broodwar->drawTextScreen(Position(0, 35), s.c_str());
		}
	};


	typedef std::pair<AUnitSet*, AUnit*> UnitSetUnitPair;

	class UnitsManager{
	private:
		bool m_initialized = false;
		static UnitsManager* m_instance;
		std::set<AUnit*> m_allUnits;
		std::map<BWAPI::UnitType, std::set<AUnitSet*>> m_unitSets;
		UnitsCounter m_unitsCounter, m_finishedUnitsCounter;
		std::map<int, int> m_knownUnitIDs;
		void setUnitSetsDrawPosition();
		int m_availableMinerals, m_availableGas;
		BWAPI::UnitType m_workerType;
	public:
		UnitsManager() {}
		static UnitsManager* UnitsManager::getInstance();
		void init();
		void addUnit(BWAPI::Unit unit);
		void removeUnit(BWAPI::Unit unit);
		void addUnitSet(AUnitSet* unitSet);
		void onFrame();
		void moveUnit(UnitSetUnitPair s, AUnitSet * d) const;
		void draw();
		const UnitsCounter& unitsCounter() const { return m_unitsCounter; }
		const UnitsCounter& finishedUnitsCounter() const { return m_finishedUnitsCounter; }
		int availableMinerals() const { return m_availableMinerals; }
		int availableGas() const { return m_availableGas; }
		UnitSetUnitPair getAvailableUnit(BWAPI::UnitType unitType, BWAPI::UnitType setType, const std::string &setName);
	};


	#define UM Amorphis::UnitsManager::getInstance()


}