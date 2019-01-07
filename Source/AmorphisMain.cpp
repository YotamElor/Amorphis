#include "AmorphisMain.hpp"
#include "Utils/Logger.hpp"


using namespace std;


namespace Amorphis {


	void AmorphisMain::init()
	{
		// find initial ResourceDepot
		for (const BWAPI::Unit &unit : Broodwar->self()->getUnits()) {
			if (unit->getType().isResourceDepot()) {
				m_miningBases.push_back(new AMiningBase("MB", unit));
				m_miningBases.back()->gather(0);
			}
		}
		if (m_miningBases.size() != 1) {
			AERR("m_miningBases.size() != 1");
		}

		// assign all workers to the initial ResourceDepot
		for (const BWAPI::Unit &unit : Broodwar->self()->getUnits()) {
			if (unit->getType().isWorker()) {
				m_miningBases[0]->addWorker(unit);
			}
		}
	}

	void AmorphisMain::draw() const
	{
		for (auto miningBase : m_miningBases) {
			miningBase->draw();
		}
	}


	void AmorphisMain::onFrame()
	{
		if (Broodwar->getFrameCount() == 0) {
			init();
		}

		for (auto miningBase : m_miningBases) {
			miningBase->onFrame();
		}
	}


	void AmorphisMain::onUnitDiscover(BWAPI::Unit unit)
	{
		if (Broodwar->getFrameCount() == 0) {
			// dont call discover on first frame
			return;
		}
		if (unit->getPlayer()->getID() == Broodwar->self()->getID()) {
			if (unit->getType().isWorker()) {
				m_miningBases[0]->addWorker(unit);
			}
		}
		else if (unit->getPlayer()->getID() == Broodwar->enemy()->getID())
		{
		}
	}


}
