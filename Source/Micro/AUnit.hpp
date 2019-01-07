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

		AUnit(BWAPI::Unit unit) : m_unit(unit) {}
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
		} m_state = Idle;
		const char* toString(State state) const;

		const BWAPI::Unit unit() const { return m_unit; }
		bool isAlive() const { return m_unit->exists(); }
		void onFrame() { if (isAlive()) onFrame_(); }

		virtual void draw() const;
		State state() const { return m_state; }
		AUnitSet const* unitSet() const { return m_unitSet;  }
		void setUnitSet(AUnitSet const* unitSet) { m_unitSet = unitSet;  }

		virtual void attack(BWAPI::Unit unit);
		virtual void move(BWAPI::Position position);
		virtual void gather(BWEM::Ressource const* resource);
	};


}