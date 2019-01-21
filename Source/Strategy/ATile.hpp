#pragma once
#include <BWAPI.h>

#include "bwem/map.h"
#include "bwem/area.h"


namespace Amorphis {


	class ATile {
		const BWAPI::TilePosition m_position;
		const BWEM::Tile const* m_bwemTile;
	public:
		ATile() : m_bwemTile(NULL), m_position(0,0) {}
		ATile(BWAPI::TilePosition);
		BWAPI::Position position() const { return BWAPI::Position(m_position); }
	};


}