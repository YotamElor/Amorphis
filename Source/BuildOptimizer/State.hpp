#pragma once
#include "Action.hpp"
#include "MiningRate.hpp"
#include "Utils/Logger.hpp"


namespace BuildOptimizerNamespace {


	class IncomeData {
		int m_numMineralPatches=0, m_numWorkers=0;
	public:
		IncomeData() {}
		IncomeData(int numMineralPatches, int numWorkers) : m_numMineralPatches(numMineralPatches), m_numWorkers(numWorkers) {}
		int numWorkers() const { return m_numWorkers; };
		int removeWorker() { if (m_numWorkers == 0) AERR("removeWorker m_numWorkers==0"); m_numWorkers--; }
		int addWorker() { m_numWorkers++; }
		double miningRate() const { return calcMiningRate(m_numMineralPatches, m_numWorkers); }
	};


	class ResourceTimed {
		Resource m_resource;
		int m_availableFrame;
	public:
		ResourceTimed(const Resource &resource, int availableFrame) : m_resource(resource), m_availableFrame(availableFrame) {}
		Resource type() const { return m_resource; }
		int availableFrame() const { return m_availableFrame; }
	};


	struct ResourceTimedCmp {
		bool operator () (const ResourceTimed& lhs, const ResourceTimed& rhs) {
			return lhs.availableFrame() <= rhs.availableFrame();
		}
	};


	class ActionInProgress {
		Resource m_product;
		int m_doneFrame;
	public:
		ActionInProgress(const Resource &product, int doneFrame) : m_product(product), m_doneFrame(doneFrame) {}
		const Resource &product() const { return m_product; }
		int doneFrame() const { return m_doneFrame; }
	};


	struct ActionInProgressCmp {
		bool operator () (const ActionInProgress& lhs, const ActionInProgress& rhs) {
			return lhs.doneFrame() <= rhs.doneFrame();
		}
	};


	class State {
	public:
		int m_frame;
		IncomeData m_incomeData;
		std::map< BWAPI::UnitType, std::set<ResourceTimed, ResourceTimedCmp> > m_resources;
		std::set<ActionInProgress, ActionInProgressCmp> m_actionsInProgress;

		State() {}
	};


}