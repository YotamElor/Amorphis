#pragma once
#include <BWAPI.h>
#include "bwem/base.h"
#include "Micro/WorkerUnitSet.hpp"
#include "AMineralPatch.hpp"


namespace Amorphis {


	class AMiningBase {
		BWAPI::Unit m_resourceDepot;
		WorkerUnitSet *m_workers;
		std::string m_name;
		std::vector<AMineralPatch> m_minerals;
		int m_numGasWorkers;
	public:
		AMiningBase(const std::string &name, BWAPI::Unit resourceDepot);
		void draw() const;
		void onFrame();
		void addWorker(BWAPI::Unit unit);
		const std::vector<AMineralPatch>& minerals() const { return m_minerals; }
		BWAPI::Unit getNextMineralPatch();
		bool build(BWAPI::UnitType whatToBuild);
	};


}