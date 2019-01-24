#include "BuildOptimizer.hpp"
#include "Utils/Logger.hpp"
#include "UnitsManager.hpp"


using namespace BWAPI;
using namespace BWAPI::UnitTypes;
using namespace std;


namespace BuildOptimizerNamespace {


	BuildOptimizer::BuildOptimizer()
	{
		m_initialState.m_frame = 0;
		m_initialState.m_mineralBases.push_back( MineralBase(9, 4) );
		m_initialState.m_minerals = Broodwar->self()->minerals();
		m_initialState.m_gas = Broodwar->self()->gas();
		m_initialState.m_freeSupply = Broodwar->self()->supplyTotal() - Broodwar->self()->supplyUsed();
		m_initialState.m_resources.insert(Resource(Zerg_Larva, UM->unitsCounter().getCounter(Zerg_Larva), 0));
		ALOG(m_initialState.toString());

		Action action(Zerg_Drone);
		ALOG(action.toString());

		m_initialState.doAction(action);
		ALOG(m_initialState.toString());

		int legalFrame = m_initialState.legalFrame(action);
		ALOG(string("legalFrame = ") + to_string(legalFrame));

		ALOG(string("Frames to 50 = ") + to_string(m_initialState.framesUntilTargetResources(50)));
		ALOG(string("Frames to 100 = ") + to_string(m_initialState.framesUntilTargetResources(100)));
	}

}