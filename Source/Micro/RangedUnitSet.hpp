#pragma once
#include "AUnitSet.hpp"
#include "EnemyUnitSet.hpp"


namespace Amorphis {


	class RangedUnitSet : public AUnitSet {
	protected:
		EnemyUnitSet *m_enemyUnitSet;
		BWAPI::Unit m_currentTarget = NULL;

		virtual void onFrame_();

	public:
		RangedUnitSet() {}
		RangedUnitSet(std::string name, BWAPI::UnitType type) : AUnitSet(name, type) {}

		virtual void setEnemy(EnemyUnitSet *enemyUnitSet);
		virtual void draw() const;
	};


}