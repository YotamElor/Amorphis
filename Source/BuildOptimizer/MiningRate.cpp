#include "MiningRate.hpp"
#include "Utils/Logger.hpp"


using namespace Amorphis;


namespace BuildOptimizerNamespace {

	
	double calcMiningRate(int numPatches, int numWorkers) {
		const double MiningRate[4] = { 0, 0.0465, 2.*0.0435, 0.1 };
		if (numWorkers >= 3 * numPatches) {
			return MiningRate[3] * (double)numPatches;
		}
		double sum = 0.;
		while (numPatches>0) {
			int workersOnPatch = numWorkers / numPatches;
			sum += MiningRate[workersOnPatch];
			numWorkers -= workersOnPatch;
			numPatches--;
		}
		if (numWorkers != 0) {
			AERR("numWorkers != 0");
		}
		return sum;
	}


}