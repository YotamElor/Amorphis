#pragma once
#include "Micro/AUnit.hpp"
#include <set>


namespace Amorphis {


	BWAPI::Unit getClosestUnit(const std::vector<AUnit*> myUnits, const std::vector<BWAPI::Unit> &enemyUnits);


}