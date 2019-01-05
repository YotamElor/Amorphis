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
		for (int i = m_units.size() - 1; i >= 0; i--) {
			if (!m_units[i]->isAlive()) {
				m_units.erase(m_units.begin() + i);
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

		vector< vector<int> > distancesMatrix;
		for (auto itUnit = m_units.begin(); itUnit != m_units.end(); itUnit++) {
			vector<int> distanceToUnit;
			for (auto itPos = f.positions().begin(); itPos != f.positions().end(); itPos++) {
				distanceToUnit.push_back((*itUnit)->unit()->getDistance(*itPos));
			}
			distancesMatrix.push_back(distanceToUnit);
		}

		for (int i = 0; i < m_units.size(); i++) {
			int maxMinDistance = -1, selectedUnit = -1, selectedPosition = -1;
			for (int unitIdx = 0; unitIdx < m_units.size(); unitIdx++) {
				int minDistance = INT_MAX;
				int minDistancePosIdx = -1;
				for (int positionIdx = 0; positionIdx < m_units.size(); positionIdx++) {
					const int d = distancesMatrix[unitIdx][positionIdx];
					//ALOG(to_string(unitIdx) + string(" ") + to_string(positionIdx) + string(" ") + to_string(d));
					if (d < minDistance) {
						minDistance = d;
						minDistancePosIdx = positionIdx;
					}
				}
				if (minDistance > maxMinDistance) {
					maxMinDistance = minDistance;
					selectedUnit = unitIdx;
					selectedPosition = minDistancePosIdx;
				}
			}
			//ALOG(string("selectedUnit = ")+std::to_string(selectedUnit));
			//ALOG(string("selectedPosition = ") + std::to_string(selectedPosition));
			m_units[selectedUnit]->move(f.positions()[selectedPosition]);
			for (int j = 0; j < m_units.size(); j++) {
				distancesMatrix[j][selectedPosition] = INT_MAX;
				distancesMatrix[selectedUnit][j] = INT_MAX;
			}
			distancesMatrix[selectedUnit][selectedPosition] = -1;
		}
		m_state = MoveFormation;
	}
}