#pragma once
#include <BWAPI.h>
#include "../DisplaySettings.hpp"
#include <set>


namespace Amorphis {


	class EnemyUnitSet {
		std::set<BWAPI::Unit> m_units;
	public:
		void insert(BWAPI::Unit unit);
		void removeDead();
		int size() const { return m_units.size(); }
		const std::set<BWAPI::Unit>& units() const { return m_units;  }
	};


}