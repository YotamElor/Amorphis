#include "Strategy.hpp"
#include "Utils/DisplaySettings.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace BWAPI;
using namespace BWAPI::UnitTypes;
using namespace std;


namespace Amorphis {


	Strategy::Strategy()
	{
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
			PlanItem planItem(true, false);
			planItem.trigger.unitsHaveLessThan(Zerg_Spawning_Pool, 1);
			planItem.action.buildUnit(Zerg_Spawning_Pool);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem;
			planItem.trigger.unitsHaveLessThan(Zerg_Drone, 9);
			planItem.action.buildUnit(Zerg_Drone);
			m_plan.push_back(planItem);
		}
		{
			PlanItem planItem(true, false);
			planItem.trigger.unitsHaveLessThan(Zerg_Extractor, 1);
			planItem.action.buildUnit(Zerg_Extractor);
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
		m_nextAction = PlanAction();
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
	}


}