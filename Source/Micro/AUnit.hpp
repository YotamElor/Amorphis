#pragma once
#include <BWAPI.h>


namespace Amorphis {


	class AUnit {
	protected:
		BWAPI::Unit m_unit = NULL;

		AUnit(BWAPI::Unit unit) : m_unit(unit) {}
	public:
		virtual void draw() const = 0;
	};


}