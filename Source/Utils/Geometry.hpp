#pragma once
#include "../Micro/AUnit.hpp"
#include <set>


namespace Amorphis {


	BWAPI::Unit getClosestUnit(const std::set<AUnit*> myUnits, const std::set<BWAPI::Unit> &enemyUnits);


}