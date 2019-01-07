#pragma once
#include <BWAPI.h>
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


namespace Amorphis {


	class AMiningBase {
		BWAPI::Unit m_resourceDepot;
		std::vector<BWAPI::Unit> m_minerals;
		std::vector<BWAPI::Unit> m_gases;
	public:
		AMiningBase() {}
		AMiningBase(BWAPI::Unit resourceDepot);
		void draw() const;
		void onFrame();
	};


}