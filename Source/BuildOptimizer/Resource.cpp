#include "MiningRate.hpp"
#include "Utils/Logger.hpp"
#include "Action.hpp"


using namespace std;
using namespace BWAPI;
using namespace BWAPI::UnitTypes;


namespace BuildOptimizerNamespace {


	std::string Resource::toString() const
	{
		string s = "";
		if (m_type==unit) {
			s += m_unitType.toString() + string("(") + to_string(m_amount) + string(")");
		}
		else {
			AERR("ERROR: Resource::toString()");
		}
		s += string(" frame=") + to_string(m_frame);
		return s;
	}


	bool Resource::sameAs(const Resource & r) const
	{
		return (m_type == r.getType() && m_unitType == r.getUnitType());
	}


}