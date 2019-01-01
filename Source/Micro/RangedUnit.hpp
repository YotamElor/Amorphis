#pragma once
#include "AUnit.hpp"


namespace Amorphis {


	class RangedUnit : public AUnit {
	public:
		RangedUnit(BWAPI::Unit unit);
		virtual void _displayUnitName() const;
	};


}