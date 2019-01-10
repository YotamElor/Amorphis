#include "AUnit.hpp"
#include "AUnitSet.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void AUnit::displayUnitName() const
	{
		if (DisplaySettings::UnitName) {
			const Position p = m_unit->getPosition();
			const string name = (m_unitSet == NULL) ? "NULL" : m_unitSet->name();
			Broodwar->drawTextMap(p, "%s:%s", name.c_str(), toString(m_state));
			//Broodwar->drawTextMap(p, "%s:%s\n%s", name.c_str(), toString(m_state), m_unit->getLastCommand().getType().toString().c_str());
		}
	}


	void AUnit::displayTarget() const
	{
		if (DisplaySettings::moveTarget && m_state == Move) {
			Broodwar->drawCircleMap(m_targetPosition, 10, Color(50, 255, 50));
		}
	}


	void AUnit::draw() const
	{
		displayUnitName();
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


	void AUnit::gather(BWAPI::Unit unit)
	{
		AERR("AUnit::gather should not be called");
	}


	void AUnit::build(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition)
	{
		AERR("AUnit::build should not be called");
	}


	void AUnit::stop()
	{
		m_unit->stop();
		m_state = Idle;
	}


	const char * AUnit::toString(State state) const
	{
		switch (state)
		{
		case Idle: return "(I)"; break;
		case Attack: return "(A)"; break;
		case Move: return "(M)"; break;
		case GatherMinerals: return "(GM)"; break;
		case GatherGas: return "(GG)"; break;
		case Build: return "(B)"; break;
		}
		return "Error convert state to string";
	}


	void AUnit::onFrame_()
	{
	}

}