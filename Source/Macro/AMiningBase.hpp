#pragma once
#include <BWAPI.h>
#include "bwem/base.h"
#include "Micro/WorkerUnitSet.hpp"


namespace Amorphis {


	class AMiningBase {
		BWAPI::Unit m_resourceDepot;
		BWEM::Base const* m_base = NULL;
		WorkerUnitSet *m_workers;
		std::string m_name;
	public:
		AMiningBase(const std::string &name, BWAPI::Unit resourceDepot);
		void draw() const;
		void onFrame();
		void addWorker(BWAPI::Unit unit);
		BWEM::Base const* base() const { return m_base;  }
		void gather(int numGasWorkers);
	};


}