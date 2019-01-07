#include "AmorphisMain.hpp"


using namespace std;


namespace Amorphis {


	void AmorphisMain::init()
	{
	}

	void AmorphisMain::draw() const
	{
		ALOG("AmorphisMain::draw()");
		for (int i = 0; i < (int)m_miningBases.size(); i++) {
			m_miningBases[i].draw();
		}
		ALOG("AmorphisMain::draw() done");
	}


	void AmorphisMain::onFrame()
	{
		for (int i = 0; i < (int)m_miningBases.size(); i++) {
			m_miningBases[i].onFrame();
		}
	}


	void AmorphisMain::onUnitDiscover(BWAPI::Unit unit)
	{
		ALOG(string("AmorphisMain::onUnitDiscover ")+unit->getType().toString());
		if (unit->getPlayer()->getID() == Broodwar->self()->getID()) {
			if (unit->getType().isResourceDepot()) {
				m_miningBases.push_back(AMiningBase(unit));
			}
		}
		else if (unit->getPlayer()->getID() == Broodwar->enemy()->getID())
		{
		}
		ALOG("AmorphisMain::onUnitDiscover done");
	}


}
