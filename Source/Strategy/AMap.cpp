#include "AMap.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"
#include "bwem/base.h"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	AMap::AMap()
	{
	}


	void AMap::init()
	{
		m_mainBaseArea = theMap.GetArea(Broodwar->self()->getStartLocation());
		if (m_mainBaseArea->AccessibleNeighbours().size() != 1) {
			AERR("m_mainBaseArea->AccessibleNeighbours().size() != 1");
		}
		m_naturalArea = theMap.GetArea(m_mainBaseArea->AccessibleNeighbours()[0]->Id());
		if (m_naturalArea->Bases().size() != 1) {
			AERR("m_naturalArea->Bases().size() != 1");
		}
	}


	void AMap::onFrame()
	{
	}


	void AMap::draw() const
	{
		if (DisplaySettings::Map) {
			for (const ChokePoint * cp : m_naturalArea->ChokePoints()) {
				for (ChokePoint::node end : {ChokePoint::end1, ChokePoint::end2}) {
					Broodwar->drawLineMap(Position(cp->Pos(ChokePoint::middle)), Position(cp->Pos(end)), Color(200, 50, 50));
				}
			}
			for (const ChokePoint * cp : m_mainBaseArea->ChokePoints()) {
				for (ChokePoint::node end : {ChokePoint::end1, ChokePoint::end2}) {
					Broodwar->drawLineMap(Position(cp->Pos(ChokePoint::middle)), Position(cp->Pos(end)), Color(50, 50, 200));
				}
			}
			//Broodwar->drawBoxMap(Position(nextExpansionPosition()), Position(nextExpansionPosition()) + Position(100, 100), Color(150, 150, 150));
		}
	}


	BWAPI::TilePosition AMap::nextExpansionPosition() const
	{
		return m_naturalArea->Bases()[0].Location();

	}

}