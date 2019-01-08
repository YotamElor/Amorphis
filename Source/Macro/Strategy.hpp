#pragma once
#include <BWAPI.h>
#include <vector>


namespace Amorphis {


	class Strategy {
		std::map<BWAPI::UnitType, int> m_unitsCounter;
		BWAPI::UnitType m_nextToBuild = NULL;
	public:
		Strategy() {}
		void onFrame();
		BWAPI::UnitType nextToBuild() const { return m_nextToBuild; }
		void draw() const;
	};


}