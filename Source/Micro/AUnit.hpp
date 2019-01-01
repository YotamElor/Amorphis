#pragma once
#include <BWAPI.h>
#include "../DisplaySettings.hpp"


namespace Amorphis {


	class AUnit {
	protected:
		BWAPI::Unit m_unit = NULL;

		AUnit(BWAPI::Unit unit) : m_unit(unit) {}
		virtual void _displayUnitName() const = 0;
	public:
		void displayUnitName() const { _displayUnitName(); }
		const BWAPI::Unit unit() const { return m_unit; }
		bool isAlive() const { return m_unit->exists(); }
	};


}