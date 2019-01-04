#include "AUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	void AUnit::displayUnitName(const std::string &name) const
	{
		if (DisplaySettings::UnitName) {
			const Position p = m_unit->getPosition();
			Broodwar->drawTextMap(p, "%s:%s\n%s", name.c_str(), toString(m_state), m_unit->getLastCommand().getType().toString().c_str());
		}
	}


	void AUnit::displayTarget() const
	{
		if (DisplaySettings::moveTarget && m_state == Move) {
			Broodwar->drawCircleMap(m_targetPosition, 10, Color(50, 255, 50));
		}
	}


	void AUnit::draw(const std::string &name) const
	{
		displayUnitName(name);
		displayTarget();
	}


	void AUnit::attack(BWAPI::Unit unit)
	{
		m_state = Attack;
		m_targetUnit = unit;
	}


	void AUnit::move(BWAPI::Position position)
	{
		m_state = Move;
		m_targetPosition = position;
		m_unit->move(m_targetPosition);
	}

	const char * AUnit::toString(State state) const
	{
		switch (state)
		{
		case Idle: return "(I)"; break;
		case Attack: return "(A)"; break;
		case Move: return "(M)"; break;
		}
		return "Error convert state to string";
	}


	void AUnit::onFrame_()
	{
	}

}