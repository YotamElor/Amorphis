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


	void Formation::setLineFormation(BWAPI::Position center, const int numUnits, const int spacing, const double direction)
	{
		const int lineLength = spacing * numUnits;
		const Position startPos = center + Position((int)((double)lineLength / 2.*cos(direction)), (int)((double)lineLength / 2.*sin(direction)));
		const Position diff = Position((int)((double)spacing / 2.*cos(direction)), (int)((double)spacing / 2.*sin(direction)));
		for (int i = 0; i < numUnits; i++) {
			m_positions.push_back(startPos - Position((int)((double)(i*spacing)*cos(direction)), (int)((double)(i*spacing)*sin(direction))));
		}
	}

}