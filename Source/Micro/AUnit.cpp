#include "AUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	void AUnit::displayUnitName() const
	{
		if (DisplaySettings::UnitName) {
			const Position p = m_unit->getPosition();
			Broodwar->drawTextMap(p, "%s:%s\n%s", m_name.c_str(), toString(m_state), m_unit->getLastCommand().getType().toString().c_str());
		}
	}


	void AUnit::draw() const
	{
		displayUnitName();
	}


	void AUnit::attack(BWAPI::Unit unit)
	{
		m_state = Attack;
		m_currentTarget = unit;
	}


	const char * AUnit::toString(State state) const
	{
		switch (state)
		{
		case Idle: return "(I)"; break;
		case Attack: return "(A)"; break;
		}
		return "Error convert state to string";
	}


	void AUnit::onFrame_() const
	{
		if (m_unit->isAttackFrame()) {
			// never interfere with an attack while the animation is running
			return;
		}
		if (m_state == Attack) {
			if (m_unit->getGroundWeaponCooldown() == 0 && m_unit->isInWeaponRange(m_currentTarget)) {
				// can shoot the target
				if (m_unit->getLastCommand().getType() != UnitCommandTypes::Enum::Hold_Position) {
					m_unit->holdPosition();
				}
			} else if (m_unit->getLastCommand().getType()!= UnitCommandTypes::Enum::Attack_Unit || m_unit->getLastCommand().getTarget()!=m_currentTarget) {
				m_unit->attack(m_currentTarget);
			}
		}
	}

}