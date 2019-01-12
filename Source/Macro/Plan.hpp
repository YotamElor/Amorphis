#pragma once
#include <BWAPI.h>
#include <vector>
#include <set>


namespace Amorphis {


	class PlanTrigger {
	public:
		enum PlanTriggerType { NotSet=0, UnitsHaveLessThan=1, FreeSupplyLessThan=2 };
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
		void freeSupplyLessThan(int number) {
			m_type = FreeSupplyLessThan;
			m_number = number;
		}
		bool check() const;
		std::string toString() const;
	};


	class PlanAction {
	public:
		enum PlanActionType { NotSet=0, BuildUnit=1 };
		const char* toString(PlanActionType type) const;
	private:
		PlanActionType m_type = NotSet;
		BWAPI::UnitType m_unitType = BWAPI::UnitTypes::None;
	public:
		void buildUnit(BWAPI::UnitType unitType) {
			m_type = BuildUnit;
			m_unitType = unitType;
		}
		PlanActionType type() const { return m_type; }
		BWAPI::UnitType unitType() const { return m_unitType;  }
		std::string toString() const;
	};


	class PlanItem {
		bool m_blocking, m_removeWhenDone;
	public:
		PlanItem(bool blocking = true, bool removeWhenDone = true) : m_blocking(blocking), m_removeWhenDone(removeWhenDone) {}
		PlanTrigger trigger;
		PlanAction action;
		bool blocking() const { return m_blocking; }
		bool removeWhenDone() const { return m_removeWhenDone; }
	};


	typedef std::vector< PlanItem > planType;


}