#pragma once
#include "Action.hpp"
#include "Utils/Logger.hpp"


namespace BuildOptimizerNamespace {


	class MineralBase {
		int m_numMineralPatches=0, m_numWorkers=0;
	public:
		MineralBase() {}
		MineralBase(int numMineralPatches, int numWorkers) : m_numMineralPatches(numMineralPatches), m_numWorkers(numWorkers) {}
		int numWorkers() const { return m_numWorkers; };
		int removeWorker() { if (m_numWorkers == 0) AERR("removeWorker m_numWorkers==0"); m_numWorkers--; }
		int addWorker() { m_numWorkers++; }
		double miningRate() const;
		std::string toString() const;
	};


	class State {
		static const int maxLegalFrame = 99999;
		ResourceSet::iterator getAvailableResource(const Resource &resource);
	public:
		int m_frame, m_minerals, m_gas, m_freeSupply;
		std::vector<MineralBase> m_mineralBases;
		ResourceSet m_resources, m_actionsInProgress;

		State() {}
		void doAction(const Action &action);

		std::string toString() const;
		int framesUntilTargetResources(int targetMinerals) const;
		int legalFrame(const Resource &resource) const;
		int legalFrame(const Action &action) const;
	};


}