#pragma once
#include "AUnitSet.hpp"
#include "EnemyUnitSet.hpp"


namespace Amorphis {

	
	class AMiningBase;


	class WorkerUnitSet : public AUnitSet {
	protected:
		AMiningBase const* m_miningBase = NULL;
		virtual void onFrame_();
		int m_numGasWorkers;

	public:
		WorkerUnitSet() {}
		WorkerUnitSet(std::string name, BWAPI::UnitType type) : AUnitSet(name, type) {}
		virtual void draw() const;
		void gather(AMiningBase const* miningBase, const int numGasWorkers);
	};


}