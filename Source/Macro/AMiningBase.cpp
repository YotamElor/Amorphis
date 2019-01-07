#include "AMiningBase.hpp"

using namespace BWAPI;


namespace Amorphis {


	AMiningBase::AMiningBase(BWAPI::Unit resourceDepot)
	{
		m_resourceDepot = resourceDepot;
	}

	void AMiningBase::draw() const
	{
		Broodwar->drawBoxMap(m_resourceDepot->getPosition(), m_resourceDepot->getPosition() + Position(m_resourceDepot->getType().tileSize()), Color(200, 200, 200));
	}


	void AMiningBase::onFrame()
	{
	}
}