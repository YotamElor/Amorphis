#include "EnemyUnitSet.hpp"

using namespace BWAPI;
using namespace std;

namespace Amorphis {


	void EnemyUnitSet::insert(BWAPI::Unit unit)
	{
		m_units.push_back(unit);
	}


	void EnemyUnitSet::removeDead()
	{
		vector< std::vector<Unit>::iterator > toDelete;
		for (auto it = m_units.begin(); it != m_units.end(); it++) {
			if (!(*it)->exists()) {
				toDelete.push_back(it);
			}
		}
		if (toDelete.size() > 0) {
			for (int i = 0; i < (int)toDelete.size(); i++) {
				m_units.erase(toDelete[i]);
			}
		}
	}


}