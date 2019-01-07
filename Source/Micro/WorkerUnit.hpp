#pragma once
#include "AUnit.hpp"
#include "bwem/neutral.h"


namespace Amorphis {


	class WorkerUnit : public AUnit {
	protected:
		virtual void onFrame_();
	public:
		WorkerUnit(BWAPI::Unit unit);
		void gather(BWEM::Ressource const* resource);
	};


}