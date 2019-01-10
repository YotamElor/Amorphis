#pragma once
#include <BWAPI.h>
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "bwem/neutral.h"


namespace Amorphis {


	class AUnitSet;


	class AUnit {
	protected:
		BWAPI::Unit m_unit = NULL;
		BWAPI::Unit m_targetUnit = NULL;
		BWAPI::Position m_targetPosition;
		AUnitSet const* m_unitSet = NULL;

		virtual void displayUnitName() const;
		virtual void displayTarget() const;

		virtual void onFrame_();

	public:
		enum State {
			Idle,
			Attack,
			Move,
			GatherMinerals,
			GatherGas,
			Build,
		} m_state = Idle;
		const char* toString(State state) const;

		AUnit(BWAPI::Unit unit) : m_unit(unit) {}
		const BWAPI::Unit unit() const { return m_unit; }
		bool isAlive() const { return m_unit->exists(); }
		void onFrame() { if (isAlive()) onFrame_(); }

		State state() const { return m_state; }
		AUnitSet const* unitSet() const { return m_unitSet; }
		const BWAPI::Unit targetUnit() const { return m_targetUnit; }
		void setUnitSet(AUnitSet const* unitSet) { m_unitSet = unitSet;  }
		void setUnitSetNULL() { m_unitSet = NULL;  }

		virtual void draw() const;
		virtual BWAPI::UnitType getType() const { return m_unit->getType(); }
		virtual BWAPI::UnitType getFinalType() const { return (m_unit->getType() == BWAPI::UnitTypes::Zerg_Egg) ? m_unit->getLastCommand().getUnitType() : getType(); }

		virtual void attack(BWAPI::Unit unit);
		virtual void move(BWAPI::Position position);
		virtual void gather(BWAPI::Unit unit);
		virtual void stop();
		virtual void build(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition);
	};


}