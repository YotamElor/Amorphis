#pragma once
#include <BWAPI.h>
#include <set>


namespace BuildOptimizerNamespace {

	
	class Resource {
	public:
		enum ResourceType {unit=0};
	private:
		ResourceType m_type;
		BWAPI::UnitType m_unitType = BWAPI::UnitTypes::None;
		mutable int m_amount;
		int m_frame;
	public:
		Resource() {}
		Resource(BWAPI::UnitType unitType, int amount, int frame) : m_type(unit), m_unitType(unitType), m_amount(amount), m_frame(frame) {}
		//Resource(ResourceType type, int amount) : m_type(type), m_amount(amount) {}
		ResourceType type() const { return m_type; }
		int amount() const { return m_amount; }
		void setAmount(int amount) const { m_amount = amount; } // not really const, m_amount is mutable :)
		BWAPI::UnitType unitType() const { return m_unitType; }
		std::string toString() const;
		int frame() const { return m_frame; }
		void setFrame(int frame) { m_frame = frame; }
		bool sameAs(const Resource &r) const;
		ResourceType getType() const { return m_type; }
		BWAPI::UnitType getUnitType() const { return m_unitType; }
	};


	struct ResourceCmp {
		bool operator () (const Resource& lhs, const Resource& rhs) {
			return lhs.frame() < rhs.frame();
		}
	};


	typedef std::set<Resource, ResourceCmp> ResourceSet;


}