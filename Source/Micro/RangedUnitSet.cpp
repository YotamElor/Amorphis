#include "RangedUnitSet.hpp"
#include "Utils/Geometry.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void RangedUnitSet::onFrame_()
	{
		if (m_state == Idle && m_units.size() == 4) {
			Formation f;
			f.setLineFormation(center(), m_units.size(), 50, 3.14*0.25);
			moveFormation(f);
		}

		if (m_state == Attack) {
			if (!m_currentTarget->exists()) {
				if (m_enemyUnitSet->units().size() > 0) {
					m_currentTarget = getClosestUnit(m_units, m_enemyUnitSet->units());
				} else {
					m_state = Idle;
					m_currentTarget = NULL;
				}
			}
		}

		if (m_state == Attack) {
			for (auto it = m_units.begin(); it != m_units.end(); it++) {
				(*it)->attack(m_currentTarget);
			}
		}

		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			(*it)->onFrame();
		}
	}


	void RangedUnitSet::draw() const
	{
		AUnitSet::draw();
		if (DisplaySettings::AUnitSetBox) {
			Broodwar->drawTextScreen(m_textPosition, "\n%s", toString(m_state));
		}
		if (DisplaySettings::Target) {
			if (m_currentTarget != NULL && m_currentTarget->exists()) {
				Broodwar->drawCircleMap(m_currentTarget->getPosition(), 5, Color(255, 0, 0));
				Broodwar->drawCircleMap(m_currentTarget->getPosition(), 10, Color(255, 20, 20));
				Broodwar->drawCircleMap(m_currentTarget->getPosition(), 15, Color(255, 40, 40));
			}
		}
	}


	void RangedUnitSet::setEnemy(EnemyUnitSet * enemyUnitSet)
	{
		m_enemyUnitSet = enemyUnitSet;
		m_state = Attack;
		m_currentTarget = *(m_enemyUnitSet->units().begin());
	}


}