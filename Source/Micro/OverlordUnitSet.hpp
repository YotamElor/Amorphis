#pragma once
#include "AUnitSet.hpp"
#include "EnemyUnitSet.hpp"


namespace Amorphis {


	class OverlordUnitSet : public AUnitSet {
	protected:
		EnemyUnitSet *m_enemyUnitSet;
		BWAPI::Unit m_currentTarget = NULL;

		virtual void onFrame_();

	public:
		OverlordUnitSet() {}
		OverlordUnitSet(std::string name, BWAPI::UnitType type) : AUnitSet(name, type) {}
	};


}