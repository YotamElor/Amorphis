#pragma once
#include <BWAPI.h>
#include "Macro/AMiningBase.hpp"
#include "Macro/Strategy.hpp"


using namespace BWAPI;


namespace Amorphis {


	class AmorphisMain{
		std::vector<AMiningBase*> m_miningBases;
		Strategy m_strategy;
		void init();
	public:
		void onFrame();
		void draw() const;
		void onUnitDiscover(BWAPI::Unit unit);
	};


}