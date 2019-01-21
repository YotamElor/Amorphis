#include "ATile.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	ATile::ATile(BWAPI::TilePosition tp) : m_position(tp), m_bwemTile(&theMap.GetTile(tp))
	{
		
	}


}