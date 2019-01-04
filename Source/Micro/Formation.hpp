#pragma once
#include <BWAPI.h>
#include <vector>


namespace Amorphis {


	class Formation {
		std::vector<BWAPI::Position> m_positions;

	public:
		Formation() {}
		void setPointFormation(BWAPI::Position center, const int numUnits);
		void setLineFormation(BWAPI::Position center, const int numUnits);
		const std::vector<BWAPI::Position>& positions() const { return m_positions;  }
	};


}