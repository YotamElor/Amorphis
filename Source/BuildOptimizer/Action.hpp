#pragma once
#include "Resource.hpp"

namespace BuildOptimizerNamespace {


	class Action {
		Resource m_produce;
		ResourceSet m_required, m_borrowed, m_consumed;
		int m_mineralsConsumed, m_gasConsumed, m_supplyConsumed;
	public:
		std::string toString() const;
		Action(BWAPI::UnitType type);
		const Resource& getProduce() const { return m_produce; }
		const ResourceSet& getRequired() const { return m_required; }
		const ResourceSet& getBorrowed() const { return m_borrowed; }
		const ResourceSet& getConsumed() const { return m_consumed; }
		int mineralsConsumed() const { return m_mineralsConsumed; }
		int gasConsumed() const { return m_gasConsumed; }
		int supplyConsumed() const { return m_supplyConsumed; }
	};


}