#include "Utils/Logger.hpp"
#include "State.hpp"


using namespace std;


namespace BuildOptimizerNamespace {


	double MineralBase::miningRate() const {
		const double MiningRate[4] = { 0, 0.0465, 2.*0.0435, 0.1 };

		if (m_numWorkers >= 3 * m_numMineralPatches) {
			return MiningRate[3] * (double)m_numMineralPatches;
		}

		int numWorkers = m_numWorkers;
		int numPatches = m_numMineralPatches;
		double sum = 0.;
		while (numPatches > 0) {
			int workersOnPatch = numWorkers / numPatches;
			sum += MiningRate[workersOnPatch];
			numWorkers -= workersOnPatch;
			numPatches--;
		}
		if (numWorkers != 0) {
			AERR("numWorkers != 0");
		}
		return sum;
	}


	std::string MineralBase::toString() const {
		return string("MineralBase: patches=") + to_string(m_numMineralPatches) + string(" workers=") + to_string(m_numWorkers);
	}


	void State::doAction(const Action &action)
	{
		Resource p = action.getProduce();
		const int doneFrame = p.frame() + m_frame;
		p.setFrame(doneFrame);
		m_actionsInProgress.insert(p);

		m_minerals -= action.mineralsConsumed();
		m_gas -= action.gasConsumed();
		m_freeSupply -= action.supplyConsumed();

		for (auto r : action.getRequired()) {
			const ResourceSet::iterator it = getAvailableResource(r);
		}
		for (auto b : action.getBorrowed()) {
			const ResourceSet::iterator it = getAvailableResource(b);
			Resource r(*it);
			r.setFrame(doneFrame);
			m_resources.erase(it);
			m_resources.insert(r);
		}
		for (auto c : action.getConsumed()) {
			const ResourceSet::iterator it = getAvailableResource(c);
			const int newAmount = it->amount() - c.amount();
			if (newAmount == 0) {
				m_resources.erase(it);
			}
			else if (newAmount > 0) {
				it->setAmount(newAmount);
			}
		}

	}


	std::string State::toString() const
	{
		string s = string("State: frame=") + to_string(m_frame);
		s += string(" minerals=") + to_string(m_minerals);
		s += string(" gas=") + to_string(m_gas);
		s += string(" freeSupply=") + to_string(m_freeSupply);
		for (auto m : m_mineralBases) {
			s += string("\n\t") + m.toString();
		}
		for (auto r : m_resources) {
			s += string("\n\tresource ") + r.toString();
		}
		for (auto a : m_actionsInProgress) {
			s += string("\n\tin progress ") + a.toString();
		}
		return s;
	}


	int State::framesUntilTargetResources(int targetMinerals) const
	{
		if (m_minerals > targetMinerals) {
			return 0;
		}
		double miningRate = 0.;
		for (auto m : m_mineralBases) {
			miningRate += m.miningRate();
		}
		return (int)((double)(targetMinerals-m_minerals)/miningRate);
	}


	int State::legalFrame(const Resource &resource) const
	{
		int minFrame = maxLegalFrame;
		for (auto r : m_resources) {
			if (r.sameAs(resource)) {
				minFrame = min(minFrame, r.frame());
			}
		}
		return minFrame;
	}


	int State::legalFrame(const Action &action) const
	{
		int maxFrame = 0;
		for (auto a : action.getRequired()) {
			maxFrame = max(maxFrame, legalFrame(a));
		}
		for (auto a : action.getBorrowed()) {
			maxFrame = max(maxFrame, legalFrame(a));
		}
		for (auto a : action.getConsumed()) {
			maxFrame = max(maxFrame, legalFrame(a));
		}

		// TODO gas minerals supply
		return maxFrame;
	}


	ResourceSet::iterator State::getAvailableResource(const Resource &resource)
	{
		for (ResourceSet::iterator it=m_resources.begin() ; it!=m_resources.end() ; it++) {
			if (it->sameAs(resource) && it->frame() <= m_frame) {
				return it;
			}
		}
		AERR(string("State::getAvailableResource not found : ")+ resource.toString());
		return m_resources.begin();
	}
}