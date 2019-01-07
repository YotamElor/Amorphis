#pragma once
#include <BWAPI.h>
#include "Macro/AMiningBase.hpp"


using namespace BWAPI;


namespace Amorphis {


	class AmorphisMain{
		std::vector<AMiningBase> m_miningBases;
		void init();
	public:
		void onFrame();
		void draw() const;
		void onUnitDiscover(BWAPI::Unit unit);
	};


}