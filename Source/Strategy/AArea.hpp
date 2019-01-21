#pragma once
#include <BWAPI.h>
#include "ATile.hpp"

#include "bwem/map.h"
#include "bwem/area.h"


namespace Amorphis {


	class AArea {
		const BWEM::Area const* m_bwemArea;
		std::vector<ATile> m_tiles;
	public:
		AArea() : m_bwemArea(NULL) {}
		AArea(BWEM::Area const* area);
		BWEM::Area const* bwem() const { return m_bwemArea;  }
		void addTile(ATile t) { m_tiles.push_back(ATile(t) ); }
		const std::vector<ATile>& tiles() const { return m_tiles;  }
	};


}