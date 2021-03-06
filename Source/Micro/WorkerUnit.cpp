#include "WorkerUnit.hpp"

using namespace BWAPI;


namespace Amorphis {


	WorkerUnit::WorkerUnit(BWAPI::Unit unit) : AUnit(unit)
	{
	}


	void WorkerUnit::gather(BWAPI::Unit unit)
	{
		m_targetUnit = unit;
		if (unit->getType() == UnitTypes::Resource_Mineral_Field) {
			m_state = GatherMinerals;
		}
		else if (unit->getType().isRefinery()) {
			m_state = GatherGas;
		}
		else {
			AERR(("WorkerUnit::gather type = ") + unit->getType().toString());
		}
	}


	void WorkerUnit::onFrame_()
	{
		if (m_state == GatherMinerals) {
			if (m_targetUnit == NULL || !m_targetUnit->exists()) {
				stop();
			}
			else if (!m_unit->isGatheringMinerals() || m_unit->getOrderTarget()==NULL || (!m_unit->getOrderTarget()->getType().isResourceDepot() && m_unit->getOrderTarget() != m_targetUnit)) {
				m_unit->gather(m_targetUnit);
			}
		}
		else if (m_state == GatherGas) {
			if (m_targetUnit == NULL || !m_targetUnit->exists()) {
				stop();
			}
			else if (!m_unit->isGatheringGas() || m_unit->getOrderTarget() == NULL || (!m_unit->getOrderTarget()->getType().isResourceDepot() && m_unit->getOrderTarget() != m_targetUnit)) {
				m_unit->gather(m_targetUnit);
			}
		}
		else if (m_state == Build) {
			if (m_unit->getDistance(Position(m_targetTilePosition)) > 100) {
				m_unit->move(Position(m_targetTilePosition));
			}
			else {
				m_unit->build(m_targetUnitType, m_targetTilePosition);
			}
		}
	}


	void WorkerUnit::build(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition)
	{
		m_targetUnitType = unitType;
		m_targetTilePosition = tilePosition;
		m_state = Build;
		m_mineralDebt = unitType.mineralPrice();
		m_gasDebt = unitType.gasPrice();
	}


	BWAPI::UnitType WorkerUnit::getFinalType() const {
		return (m_state==Build) ? m_unit->getLastCommand().getUnitType() : getType();
	}
}