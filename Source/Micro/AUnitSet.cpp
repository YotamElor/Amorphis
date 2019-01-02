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


	void AUnitSet::draw() const
	{
		if (DisplaySettings::AUnitSetBox) {
			Broodwar->drawBoxScreen(m_drawPositionTL, m_drawPositionBR, Color(50, 50, 50), true);
			Broodwar->drawBoxScreen(m_drawPositionTL, m_drawPositionBR, Color(200, 200, 200), false);
			Broodwar->drawTextScreen(m_text0Position, "%s : %s (%d)", m_name.c_str(), m_type.c_str(), m_units.size());
		}
		if (DisplaySettings::UnitName) {
			for (auto it = m_units.begin(); it != m_units.end(); it++) {
				(*it)->draw();
			}
		}
	}

	
	void AUnitSet::removeDead()
	{
		vector< std::set<AUnit*>::iterator > toDelete;
		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			if (!(*it)->isAlive()) {
				toDelete.push_back(it);
			}
		}
		if (toDelete.size() > 0) {
			for (int i = 0; i < (int)toDelete.size(); i++) {
				delete *toDelete[i];
				m_units.erase(toDelete[i]);
			}
		}
	}


	void AUnitSet::setDrawPosition(BWAPI::Position p)
	{
		m_drawPositionTL = p;
		m_drawPositionBR = p + Position(boxWidth,boxHeight);
		m_text0Position = p + Position(2, 0);
		m_text1Position = m_text0Position + Position(0, textHeight);
	}

	
	void AUnitSet::onFrame()
	{
		removeDead();
		onFrame_();
	}


}