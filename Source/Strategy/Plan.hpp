#pragma once
#include <BWAPI.h>
#include <vector>
#include <set>


namespace Amorphis {


	class PlanTrigger {
	public:
		enum PlanTriggerType { NotSet=0, UnitsHaveLessThan=1, UnitsHaveMoreThan=2, FreeSupplyLessThan=3, FinishedHaveMoreThan=4	};
		const char* toString(PlanTriggerType type) const;
	private:
		PlanTriggerType m_type = NotSet;
		BWAPI::UnitType m_unitType = BWAPI::UnitTypes::None;
		int m_number = -1;
	public:
		void unitsHaveLessThan(BWAPI::UnitType unitType, int number) {
			m_type = UnitsHaveLessThan;
			m_unitType = unitType;
			m_number = number;
		}
		void unitsHaveMoreThan(BWAPI::UnitType unitType, int number) {
			m_type = UnitsHaveMoreThan;
			m_unitType = unitType;
			m_number = number;
		}
		void finishedHaveMoreThan(BWAPI::UnitType unitType, int number) {
			m_type = FinishedHaveMoreThan;
			m_unitType = unitType;
			m_number = number;
		}
		void freeSupplyLessThan(int number) {
			m_type = FreeSupplyLessThan;
			m_number = number;
		}
		bool check() const;
		std::string toString() const;
	};


	class PlanAction {
	public:
		enum PlanActionType { NotSet=0, BuildUnit=1, NumGasWorkers=2, BuildBuilding=3};
		const char* toString(PlanActionType type) const;
	private:
		PlanActionType m_type = NotSet;
		BWAPI::UnitType m_unitType = BWAPI::UnitTypes::None;
		BWAPI::TilePosition m_tilePosition;
		int m_number = 0;
	public:
		void buildUnit(BWAPI::UnitType unitType) {
			m_type = BuildUnit;
			m_unitType = unitType;
		}
		void buildBuilding(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition) {
			m_type = BuildBuilding;
			m_tilePosition = tilePosition;
			m_unitType = unitType;
		}
		void numGasWorkers(int number) {
			m_type = NumGasWorkers;
			m_number = number;
		}
		PlanActionType type() const { return m_type; }
		BWAPI::UnitType unitType() const { return m_unitType;  }
		int number() const { return m_number; }
		BWAPI::TilePosition tilePosition() const { return m_tilePosition; }
		std::string toString() const;
	};


	class PlanItem {
		bool m_blocking, m_removeWhenDone, m_doOnce;
	public:
		PlanItem(bool blocking = true, bool removeWhenDone = true, bool doOnce = false) : m_blocking(blocking), m_removeWhenDone(removeWhenDone), m_doOnce(doOnce) {}
		PlanTrigger trigger;
		PlanAction action;
		bool blocking() const { return m_blocking; }
		bool removeWhenDone() const { return m_removeWhenDone; }
		bool doOnce() const { return m_doOnce; }
	};


	typedef std::vector< PlanItem > planType;


}