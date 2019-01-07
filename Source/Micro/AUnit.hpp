#pragma once
#include <BWAPI.h>
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


namespace Amorphis {


	class AUnit {
	protected:
		BWAPI::Unit m_unit = NULL;
		BWAPI::Unit m_targetUnit = NULL;
		BWAPI::Position m_targetPosition;

		AUnit(BWAPI::Unit unit) : m_unit(unit) {}
		virtual void displayUnitName(const std::string &name) const;
		virtual void displayTarget() const;

		enum State {
			Idle,
			Attack,
			Move
		} m_state = Idle;

		virtual const char* toString(State state) const;

		virtual void onFrame_();

	public:
		const BWAPI::Unit unit() const { return m_unit; }
		bool isAlive() const { return m_unit->exists(); }
		void onFrame() { if (isAlive()) onFrame_(); }

		virtual void draw(const std::string &name) const;
		virtual void attack(BWAPI::Unit unit);
		virtual void move(BWAPI::Position position);
	};


}