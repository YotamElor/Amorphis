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
		int getCounter(BWAPI::UnitType unitType) const
		{
			if (m_map.find(unitType) == m_map.end()) {
				return 0;
			}
			return m_map.find(unitType)->second;
		}
		void draw() const
		{
			std::string s = "";
			for (auto it = m_map.begin(); it != m_map.end(); it++) {
				if (it->second > 0) {
					s += it->first.toString() + std::string(" (") + std::to_string(it->second) + std::string(")\n");
				}
			}
			Broodwar->drawTextScreen(Position(0, 35), s.c_str());
		}
	};


	class UnitsManager{
	private:
		bool m_initialized = false;
		static UnitsManager* m_instance;
		std::set<AUnit*> m_allUnits;
		std::map<BWAPI::UnitType, std::set<AUnitSet*>> m_unitSets;
		UnitsCounter m_unitsCounter;
		std::map<int, int> m_knownUnitIDs;
		void setUnitSetsDrawPosition();
		int m_availableMinerals, m_availableGas;
	public:
		UnitsManager() {}
		static UnitsManager* UnitsManager::getInstance();
		void init();
		void addUnit(BWAPI::Unit unit);
		void removeUnit(BWAPI::Unit unit);
		void addUnitSet(AUnitSet* unitSet);
		void onFrame();
		void moveUnit(AUnitSet * s, AUnitSet * d, AUnit * u) const;
		void draw();
		const UnitsCounter& unitsCounter() const { return m_unitsCounter; }
		int availableMinerals() const { return m_availableMinerals; }
		int availableGas() const { return m_availableGas; }
	};


	#define UM UnitsManager::getInstance()


}