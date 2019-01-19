#include "AmorphisMain.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"
#include "bwem/bwem.h"


using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


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
		m_strategy.init();
	}


	void AmorphisMain::draw() const
	{
		UM->draw();
		for (auto miningBase : m_miningBases) {
			miningBase->draw();
		}
		m_strategy.draw();
	}


	AmorphisMain::AmorphisMain()
	{
		theMap.Initialize();
		theMap.EnableAutomaticPathAnalysis();
		bool startingLocationsOK = theMap.FindBasesForStartingLocations();
		assert(startingLocationsOK);
		init();
	}

	void AmorphisMain::onFrame()
	{
		UM->onFrame();

		for (auto miningBase : m_miningBases) {
			miningBase->onFrame();
		}

		m_strategy.onFrame();
		const PlanAction& action = m_strategy.nextAction();
		if (action.type() == PlanAction::PlanActionType::NotSet) {
		}
		else if (action.type() == PlanAction::PlanActionType::BuildUnit) {
			const UnitType unitType = action.unitType();
			if (unitType.isBuilding()) {
				AERR("unitType.isBuilding()");
			}
			if (UM->availableMinerals() >= unitType.mineralPrice() && UM->availableGas() >= unitType.gasPrice())
			{
				m_miningBases[0]->morphLarva(unitType);
			}
		}
		else if (action.type() == PlanAction::PlanActionType::BuildBuilding) {
			const UnitType unitType = action.unitType();
			if (!unitType.isBuilding()) {
				AERR("!unitType.isBuilding()");
			}
			if (UM->availableMinerals() >= unitType.mineralPrice() && UM->availableGas() >= unitType.gasPrice())
			{
				m_miningBases[0]->build(unitType, action.tilePosition());
			}
		}
		else if (action.type() == PlanAction::PlanActionType::NumGasWorkers) {
			m_miningBases[0]->setNumGasWorkers(action.number());
		}
		else {
			AERR(string("couldnt decipher it->action.type(): ") + to_string(action.type()));
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
