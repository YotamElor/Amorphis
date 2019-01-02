#pragma once
#include <BWAPI.h>
#include "../DisplaySettings.hpp"


namespace Amorphis {


	class AUnit {
	protected:
		BWAPI::Unit m_unit = NULL;
		std::string m_name;
		BWAPI::Unit m_currentTarget = NULL;

		AUnit(BWAPI::Unit unit) : m_unit(unit), m_name(m_unit->getType().c_str()) {}
		virtual void displayUnitName() const;

		enum State {
			Idle,
			Attack
		} m_state = Idle;

		virtual const char* toString(State state) const;

		virtual void onFrame_() const;

	public:
		const BWAPI::Unit unit() const { return m_unit; }
		bool isAlive() const { return m_unit->exists(); }
		void onFrame() { if (isAlive()) onFrame_(); }

		virtual void draw() const;
		virtual void attack(BWAPI::Unit unit);
	};


}