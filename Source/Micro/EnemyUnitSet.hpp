#pragma once
#include <BWAPI.h>
#include "Utils/DisplaySettings.hpp"
#include <set>


namespace Amorphis {


	class EnemyUnitSet {
		std::vector<BWAPI::Unit> m_units;
	public:
		void insert(BWAPI::Unit unit);
		void removeDead();
		int size() const { return m_units.size(); }
		const std::vector<BWAPI::Unit>& units() const { return m_units;  }
	};


}