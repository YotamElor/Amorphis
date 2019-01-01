#pragma once
#include <BWAPI.h>
#include "../DisplaySettings.hpp"
#include <set>
#include "AUnit.hpp"


namespace Amorphis {


	class AUnitSet {
	protected:
		std::set<AUnit*> m_units;
		std::string m_name;
		BWAPI::UnitType m_type;
		BWAPI::Position m_drawPositionTL, m_drawPositionBR, m_textPosition;

	public:
		static const int boxWidth = 200;
		static const int boxHeight = 15;

		AUnitSet() {}
		AUnitSet(std::string name, BWAPI::UnitType type) : m_name(name), m_type(type) {}

		void insert(AUnit *unit);
		void draw() const;
		void onFrame();
		void setDrawPosition(BWAPI::Position p);
	};


}