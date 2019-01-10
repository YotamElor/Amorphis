#include "AmorphisMain.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace std;


namespace Amorphis {


	void AmorphisMain::init()
	{
		UM->init();
		for (const BWAPI::Unit &unit : Broodwar->self()->getUnits()) {
			if (unit->getType().isResourceDepot()) {
				m_miningBases.push_back(new AMiningBase("MB", unit));
			}
		}
		if (m_miningBases.size() != 1) {
			AERR("m_miningBases.size() != 1");
		}
	}


	void AmorphisMain::draw() const
	{
		UM->draw();
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

		UM->onFrame();

		for (auto miningBase : m_miningBases) {
			miningBase->onFrame();
		}

		m_strategy.onFrame();
		UnitType nextToBuild = m_strategy.nextToBuild();
		if (nextToBuild != NULL &&
			Broodwar->self()->minerals() >= nextToBuild.mineralPrice() &&
			Broodwar->self()->gas() >= nextToBuild.gasPrice())
		{
			if (nextToBuild.isBuilding()) {
				m_miningBases[0]->build(nextToBuild);
			}
			else {
				m_miningBases[0]->morphLarva(nextToBuild);
			}
		}
	}


	void AmorphisMain::onUnitDiscover(BWAPI::Unit unit)
	{
		if (unit->getPlayer()->getID() == Broodwar->self()->getID()) {
			UM->addUnit(unit);
		}
		else if (unit->getPlayer()->getID() == Broodwar->enemy()->getID())
		{
		}
	}


	void AmorphisMain::onUnitMorph(BWAPI::Unit unit)
	{
		if (unit->getPlayer()->getID() == Broodwar->self()->getID()) {
			UM->removeUnit(unit);
			UM->addUnit(unit);
		}
	}


}
