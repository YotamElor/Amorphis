#include "AUnitSet.hpp"

using namespace BWAPI;
using namespace std;

namespace Amorphis {


	void AUnitSet::insert(AUnit *unit)
	{
		if (unit->unit()->getType() != m_type) {
			Broodwar->sendText("ERROR: unit->unit()->getType() != m_type: ");
			//throw(0);
		}
		m_units.insert(unit);
	}


	void AUnitSet::displayUnitNames() const
	{
		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			(*it)->displayUnitName();
		}
	}

}