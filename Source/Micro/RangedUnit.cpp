#include "RangedUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	RangedUnit::RangedUnit(BWAPI::Unit unit) : AUnit(unit)
	{
	}


	void RangedUnit::_displayUnitName() const
	{
		const Position p = m_unit->getPosition();
		Broodwar->drawTextMap(p, "d");
	}


}