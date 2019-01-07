#pragma once
#include <BWAPI.h>
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


namespace Amorphis {


	class AMineralPatch {
		BWAPI::Unit m_unit;
		int m_priority, m_numWorkers;
	public:
		AMineralPatch(BWAPI::Unit unit, int priority) : m_unit(unit), m_priority(priority), m_numWorkers(0) {}
		BWAPI::Unit unit() const { return m_unit;  }
		void draw() const;
		int priority() const { return m_priority;  }
		void resetNumWorkers() { m_numWorkers = 0; }
		void addWorker() { m_numWorkers++; }
		int numWorkers() const { return m_numWorkers;	}
	};

	bool AMineralPatchCmp(const AMineralPatch &a, const AMineralPatch &b);


}