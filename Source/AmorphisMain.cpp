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
		m_strategy.draw();
	}


	void AmorphisMain::onFrame()
	{
		if (Broodwar->getFrameCount() == 0) {
			init();
		}

		for (auto miningBase : m_miningBases) {
			miningBase->onFrame();
		}

		m_strategy.onFrame();
		BWAPI::UnitType nextToBuild = m_strategy.nextToBuild();
		if (nextToBuild != NULL &&
			Broodwar->self()->hasUnitTypeRequirement(nextToBuild) &&
			Broodwar->self()->minerals() >= nextToBuild.mineralPrice() &&
			Broodwar->self()->gas() >= nextToBuild.gasPrice())
		{
			m_miningBases[0]->build(nextToBuild);
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
