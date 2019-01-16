#pragma once
#include <BWAPI.h>
#include "bwem/base.h"
#include "Micro/WorkerUnitSet.hpp"
#include "AMineralPatch.hpp"


namespace Amorphis {


	class AMiningBase {
		BWEM::Base const* m_baseBwem = NULL;
		BWAPI::Unit m_resourceDepot;
		WorkerUnitSet *m_workers;
		std::string m_name;
		std::vector<AMineralPatch> m_minerals;
		std::vector<BWAPI::Unit> m_gasGysers;
		BWAPI::Position m_drawPositionTL, m_drawPositionBR, m_textPosition;
	public:
		AMiningBase(const std::string &name, BWAPI::Unit resourceDepot);
		void draw() const;
		void onFrame();
		const std::vector<AMineralPatch>& minerals() const { return m_minerals; }
		const std::vector<BWAPI::Unit>& gysers() const { return m_gasGysers; }
		BWAPI::Unit getNextMineralPatch();
		bool morphLarva(BWAPI::UnitType whatToBuild);
		bool build(BWAPI::UnitType whatToBuild);
		int larvaCount() const { return m_resourceDepot->getLarva().size(); }
		void setNumGasWorkers(int numGasWorkers) { m_workers->setNumGasWorkers(numGasWorkers); }
	};


}