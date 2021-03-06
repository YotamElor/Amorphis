#pragma once
#include "AUnitSet.hpp"
#include "EnemyUnitSet.hpp"


namespace Amorphis {

	
	class AMiningBase;


	class WorkerUnitSet : public AUnitSet {
	protected:
		AMiningBase* m_miningBase = NULL;
		virtual void onFrame_();
		int m_numGasWorkers;

	public:
		WorkerUnitSet() {}
		WorkerUnitSet(std::string name, BWAPI::UnitType type) : AUnitSet(name, type) {}
		virtual void draw() const;
		void gather(AMiningBase* miningBase, const int numGasWorkers);
		void build(BWAPI::UnitType unitType, BWAPI::TilePosition tilePosition);
		void setNumGasWorkers(int numGasWorkers) { m_numGasWorkers = numGasWorkers; }
		int numGasWorkers() const { return m_numGasWorkers; }
	};


}