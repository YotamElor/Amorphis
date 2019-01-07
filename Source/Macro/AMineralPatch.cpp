#include "AMineralPatch.hpp"

using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void AMineralPatch::draw() const
	{
		Broodwar->drawBoxMap(m_unit->getPosition(), m_unit->getPosition() + Position(35,14), Color(50, 50, 50), true);
		Broodwar->drawTextMap(m_unit->getPosition(), "%d (%d)", m_priority, m_numWorkers);
	}

	bool AMineralPatchCmp(const AMineralPatch &a, const AMineralPatch &b) {
		return a.priority() < b.priority();
	}

}