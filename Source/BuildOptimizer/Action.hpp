#pragma once
#include <BWAPI.h>
#include <set>


namespace BuildOptimizerNamespace {

	
	class Resource {
	public:
		enum ResourceType {unit=0, minerals=1, gas=2};
	private:
		ResourceType m_type;
		BWAPI::UnitType m_unitType = BWAPI::UnitTypes::None;
		int m_amount;
	public:
		Resource(BWAPI::UnitType unitType, int amount) : m_type(unit), m_unitType(unitType), m_amount(amount) {}
		Resource(ResourceType type, int amount) : m_type(type), m_amount(amount) {}
		ResourceType type() const { return m_type; }
		int amount() const { return m_amount; }
		BWAPI::UnitType unitType() const { return m_unitType; }
	};


	class Action {
	public:
		int duration;
		std::set<Resource> required, borrowed, consumed;
		Resource produce;
	};


}