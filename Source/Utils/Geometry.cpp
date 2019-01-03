#include "Geometry.hpp"


using namespace std;
using namespace BWAPI;


namespace Amorphis {


	BWAPI::Unit getClosestUnit(const std::set<AUnit*> myUnits, const std::set<BWAPI::Unit> &enemyUnits) {
		if (enemyUnits.empty() || myUnits.empty()) {
			return NULL;
		}

		int minDistanceSum = 0;
		BWAPI::Unit closestUnit = NULL;
		for (auto itEnemy = enemyUnits.begin(); itEnemy != enemyUnits.end(); itEnemy++) {
			int distanceSum = 0;
			for (auto itSelf = myUnits.begin(); itSelf != myUnits.end(); itSelf++) {
				distanceSum += (*itSelf)->unit()->getDistance(*itEnemy);
			}
			if (distanceSum < minDistanceSum || minDistanceSum == 0) {
				minDistanceSum = distanceSum;
				closestUnit = *itEnemy;
			}
		}
		return closestUnit;
	}


}