#include "Formation.hpp"

using namespace BWAPI;
using namespace std;

namespace Amorphis {


	void Formation::setPointFormation(BWAPI::Position center, const int numUnits)
	{
		for (int i = 0; i < numUnits; i++) {
			m_positions.push_back(center);
		}
	}


	void Formation::setLineFormation(BWAPI::Position center, const int numUnits)
	{
		for (int i = 0; i < numUnits; i++) {
			m_positions.push_back(center + Position(i*40,0));
		}
	}

}