#include "AMap.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"
#include "bwem/base.h"
#include "AMap.hpp"


using namespace BWAPI;
using namespace BWEM;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


namespace Amorphis {


	AMap* AMap::m_instance = NULL;


	AMap* AMap::getInstance()
	{
		if (m_instance == NULL) {
			m_instance = new AMap();
		}
		return m_instance;
	}


	void AMap::init()
	{
		for (const Area &area : theMap.Areas()) {
			m_areas[area.Id()] = AArea(&area);
		}
		for (int y = 0; y < theMap.Size().y; ++y) {
			for (int x = 0; x < theMap.Size().x; ++x) {
				const TilePosition t(x, y);
				if (theMap.GetArea(t) != NULL) {
					m_areas[theMap.GetArea(t)->Id()].addTile(t);
				}
			}
		}

		m_mainBaseArea = &m_areas[theMap.GetArea(Broodwar->self()->getStartLocation())->Id()];
		if (m_mainBaseArea->bwem()->AccessibleNeighbours().size() != 1) {
			AERR("m_mainBaseArea->AccessibleNeighbours().size() != 1");
		}
		m_naturalArea = &m_areas[m_mainBaseArea->bwem()->AccessibleNeighbours()[0]->Id()];
		if (m_naturalArea->bwem()->Bases().size() != 1) {
			AERR("m_naturalArea->Bases().size() != 1");
		}
	}


	void AMap::onFrame()
	{
	}


	void AMap::draw() const
	{
		if (DisplaySettings::Map) {
			for (const ChokePoint * cp : m_naturalArea->bwem()->ChokePoints()) {
				for (ChokePoint::node end : {ChokePoint::end1, ChokePoint::end2}) {
					Broodwar->drawLineMap(Position(cp->Pos(ChokePoint::middle)), Position(cp->Pos(end)), Color(200, 50, 50));
				}
			}
			for (const ChokePoint * cp : m_mainBaseArea->bwem()->ChokePoints()) {
				for (ChokePoint::node end : {ChokePoint::end1, ChokePoint::end2}) {
					Broodwar->drawLineMap(Position(cp->Pos(ChokePoint::middle)), Position(cp->Pos(end)), Color(50, 50, 200));
				}
			}
		}
	}


	BWAPI::TilePosition AMap::nextExpansionPosition() const
	{
		return m_naturalArea->bwem()->Bases()[0].Location();

	}

}