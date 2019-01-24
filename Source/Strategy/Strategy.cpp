#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"
#include "AMap.hpp"
#include "BuildOptimizer/BuildOptimizer.hpp"


using namespace BWAPI;
using namespace BWAPI::UnitTypes;
using namespace std;


namespace Amorphis {


	Strategy::Strategy()
	{

	}


	void Strategy::init()
	{
		Broodwar->sendText("power overwhelming");
		MAP->init();
		m_scouting.init();
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Drone, 9);
			planItem.action.buildUnit(Zerg_Drone);
			m_plan.push_back( planItem );
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Overlord, 2);
			planItem.action.buildUnit(Zerg_Overlord);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Spawning_Pool, 1);
			planItem.action.buildBuilding(Zerg_Spawning_Pool, TilePosition(0,0));
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Drone, 11);
			planItem.action.buildUnit(Zerg_Drone);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Hatchery, 2);
			planItem.action.buildBuilding(Zerg_Hatchery, MAP->nextExpansionPosition());
			m_plan.push_back(planItem);
		}
		return;
		{
			PlanItem planItem(true, true);
			planItem.trigger.unitsHaveLessThan(Zerg_Extractor, 1);
			planItem.action.buildUnit(Zerg_Extractor);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem(false, false, true);
			planItem.trigger.finishedHaveMoreThan(Zerg_Extractor, 0);
			planItem.action.numGasWorkers(3);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem(false, false, true);
			planItem.trigger.finishedHaveMoreThan(Zerg_Extractor, 0);
			planItem.action.numGasWorkers(3);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Drone, 10);
			planItem.action.buildUnit(Zerg_Drone);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem(false, false);
			planItem.trigger.freeSupplyLessThan(1);
			planItem.action.buildUnit(Zerg_Overlord);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Zergling, 100);
			planItem.action.buildUnit(Zerg_Zergling);
			m_plan.push_back(planItem);
		}
	}


	void Strategy::onFrame()
	{
		{
			BuildOptimizerNamespace::BuildOptimizer buildOptimizer;
		}
		AERR("done");

		m_scouting.onFrame();
		m_nextAction = PlanAction();
		const int droneTargetCount = 23;
		const int numPatches = 9;
		if (UM->unitsCounter().getCounter(Zerg_Overlord) < 4) {
			m_nextAction.buildUnit(Zerg_Overlord);
		}
		else if (UM->unitsCounter().getCounter(Zerg_Drone) < droneTargetCount) {
			m_nextAction.buildUnit(Zerg_Drone);
		}
		if (UM->finishedUnitsCounter().getCounter(Zerg_Drone) == droneTargetCount) {
			if (startCountFrame == 0) {
				startCountFrame = Broodwar->getFrameCount();
				startCountMinerals = Broodwar->self()->minerals();
			}
			else if (Broodwar->getFrameCount() % 1000 == 0) {
				int frameDiff = Broodwar->getFrameCount() - startCountFrame;
				int mineralsDiff = Broodwar->self()->minerals() - startCountMinerals;
				double miningRate = (double)mineralsDiff / (double)frameDiff;
//				double ratePred = BuildOptimizerNamespace::calcMiningRate(numPatches, droneTargetCount);
//				Broodwar->sendText("%d : rate = %f calc = %f diff = %d%%", droneTargetCount, miningRate, ratePred, (int)((miningRate / ratePred - 1.)*100.));
			}
		}
		return;

		bool readMoreOfPlan = true;
		if (!m_activePlan.empty()) {
			for (int i = 0; i < (int)m_activePlan.size(); i++) {
				if (m_activePlan[i].blocking() && m_activePlan[i].trigger.check()) {
					readMoreOfPlan = false;
					break;
				}
			}
		}
		if (readMoreOfPlan && !m_plan.empty()) {
			m_activePlan.push_back(m_plan[0]);
			m_plan.erase(m_plan.begin());
		}
		if (!m_activePlan.empty()) {
			for (auto it = m_activePlan.begin(); it != m_activePlan.end(); ) {
				if (it->trigger.check()) {
					m_nextAction = it->action;
					if (it->doOnce()) {
						it = m_activePlan.erase(it);
					}
					break;
				}
				else {
					if (it->removeWhenDone()) {
						it = m_activePlan.erase(it);
					}
					else {
						it++;
					}
				}
			}
		}
	}


	void Strategy::draw() const
	{
		if (DisplaySettings::Strategy) {
			string s = m_nextAction.toString();
			for (int i = 0; i < (int)m_activePlan.size(); i++) {
				s += string("\n") + m_activePlan[i].trigger.toString() + string("\n==>") + m_activePlan[i].action.toString();
			}
			Broodwar->drawTextScreen(Position(120, 20), s.c_str());
		}
		MAP->draw();
	}


}