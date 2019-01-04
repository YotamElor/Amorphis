#include "AUnitSet.hpp"

using namespace BWAPI;
using namespace std;

namespace Amorphis {


	void AUnitSet::insert(AUnit *unit)
	{
		if (unit->unit()->getType() != m_type) {
			ALOG(string("unit->unit()->getType() = ") + unit->unit()->getType().c_str());
			ALOG(string("unit->unit()->getType() = ") + m_type.c_str());
			AERR("ERROR:AUnitSet::insert: unit->unit()->getType() != m_type");
		}
		m_units.push_back(unit);
	}


	void AUnitSet::draw() const
	{
		if (DisplaySettings::AUnitSetBox) {
			Broodwar->drawBoxScreen(m_drawPositionTL, m_drawPositionBR, Color(50, 50, 50), true);
			Broodwar->drawBoxScreen(m_drawPositionTL, m_drawPositionBR, Color(200, 200, 200), false);
			Broodwar->drawTextScreen(m_textPosition, "%s : %s (%d)", m_name.c_str(), m_type.c_str(), m_units.size());
		}
		if (DisplaySettings::UnitName) {
			for (auto it = m_units.begin(); it != m_units.end(); it++) {
				(*it)->draw(m_name);
			}
		}
	}

	
	void AUnitSet::removeDead()
	{
		vector< std::vector<AUnit*>::iterator > toDelete;
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
		m_textPosition = p + Position(2, 0);
	}

	
	void AUnitSet::onFrame()
	{
		removeDead();
		onFrame_();
	}


	BWAPI::Position AUnitSet::center() const
	{
		BWAPI::Position sum(0, 0);
		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			if ((*it)->isAlive()) {
				sum += (*it)->unit()->getPosition();
			}
		}
		sum /= m_units.size();
		return sum;
	}


	const char * AUnitSet::toString(State state) const
	{
		switch (state)
		{
		case Idle: return "Idle"; break;
		case Attack: return "Attack"; break;
		case Move: return "Move"; break;
		case MoveFormation: return "MoveFormation"; break;
		}
		return "Error convert state to string";
	}


	void AUnitSet::moveFormation(const Formation &f)
	{
		if (f.positions().size() != m_units.size()) {
			AERR("ERROR:AUnitSet::moveFormation: f.positions.size() != m_units.size()");
		}
		/*
		vector< vector<int> > distancesMatrix;
		for (auto itUnit = m_units.begin(); itUnit != m_units.end(); itUnit++) {
			vector<int> distanceToUnit;
			for (auto itPos = f.positions().begin(); itPos != f.positions().end(); itPos++) {
				distanceToUnit.push_back((*itUnit)->unit()->getDistance(*itPos));
			}
			distancesMatrix.push_back(distanceToUnit);
		}

		vector<int> selectedPositionForUnits(m_units.size(), -1);
		for (int i = 0; i < m_units.size(); i++) {
			int maxMinDistance = 0, selectedUnit = -1, selectedPosition = -1;
			int unitIdx = 0;
			for (auto itUnit = m_units.begin(); itUnit != m_units.end(); itUnit++, unitIdx++) {
				int minDistance = INT_MAX;
				for (int positionIdx = 0; positionIdx < m_units.size(); positionIdx++) {
					const int d = m_units[unitIdx]

				}
			}
		} */
	}
}