#include "RangedUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	RangedUnit::RangedUnit(BWAPI::Unit unit) : AUnit(unit)
	{
	}


	void RangedUnit::onFrame_()
	{
		if (m_unit->isAttackFrame()) {
			// never interfere with an attack while the animation is running
			return;
		}
		if (m_state == Attack) {
			if (m_unit->getGroundWeaponCooldown() == 0 && m_unit->isInWeaponRange(m_targetUnit)) {
				// can shoot the target
				if (m_unit->getLastCommand().getType() != UnitCommandTypes::Enum::Hold_Position) {
					m_unit->holdPosition();
				}
			}
			else if (m_unit->getLastCommand().getType() != UnitCommandTypes::Enum::Attack_Unit || m_unit->getLastCommand().getTarget() != m_targetUnit) {
				m_unit->attack(m_targetUnit);
			}
		}
		else if (m_state == Move) {
			if (Broodwar->getFrameCount() > m_unit->getLastCommandFrame() + 10) {
				m_unit->move(m_targetPosition);
			}
		}
	}

}