#include "EnemyUnitSet.hpp"
#include "Utils/Logger.hpp"


using namespace BWAPI;
using namespace std;


namespace Amorphis {


	void EnemyUnitSet::insert(BWAPI::Unit unit)
	{
		m_units.push_back(unit);
	}


	void EnemyUnitSet::removeDead()
	{
		for (int i = m_units.size() - 1; i >= 0; i--) {
			if (!m_units[i]->exists()) {
				ALOG(string("removing ") + to_string(i));
				m_units.erase(m_units.begin() + i);
				ALOG(string("removing ") + to_string(i) + string(" done"));
			}
		}
	}


}