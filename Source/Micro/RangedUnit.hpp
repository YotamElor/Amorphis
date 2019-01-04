#pragma once
#include "AUnit.hpp"


namespace Amorphis {


	class RangedUnit : public AUnit {
	protected:
		virtual void onFrame_();
	public:
		RangedUnit(BWAPI::Unit unit);
	};


}