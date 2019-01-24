#include "Action.hpp"
#include "Utils/Logger.hpp"


using namespace std;
using namespace BWAPI;
using namespace BWAPI::UnitTypes;


namespace BuildOptimizerNamespace {


	std::string Action::toString() const
	{
		string s = "Action";
		s += string(" minerals=") + to_string(m_mineralsConsumed);
		s += string(" gas=") + to_string(m_gasConsumed);
		s += string(" supply=") + to_string(m_supplyConsumed);
		s += string("\n\tproduce ") + m_produce.toString();
		for (auto a : m_required) {
			s += string("\n\trequired ") + a.toString();
		}
		for (auto a : m_borrowed) {
			s += string("\n\tborrowed ") + a.toString();
		}
		for (auto a : m_consumed) {
			s += string("\n\tconsumed ") + a.toString();
		}
		return s;
	}


	Action::Action(BWAPI::UnitType type)
	{
		m_mineralsConsumed = type.mineralPrice();
		m_gasConsumed = type.gasPrice();
		m_supplyConsumed = type.supplyRequired();
		m_produce = Resource(type, type.isTwoUnitsInOneEgg() ? 2 : 1, type.buildTime());
		for (auto a : type.requiredUnits()) {
			if (a.first.isBuilding()) {
				m_required.insert(Resource(a.first, 1, 0));
			}
			else {
				m_consumed.insert(Resource(a.first, 1, 0));
			}
		}
		
		
	}

}