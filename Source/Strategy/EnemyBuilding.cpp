#include "EnemyBuilding.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	EnemyBuilding::EnemyBuilding(BWAPI::Unit unit) : m_unit(unit)
	{
		
	}


}