#pragma once
#include "AUnit.hpp"
#include <set>


namespace Amorphis {


	class AUnitSet {
	protected:
		std::set<AUnit*> m_units;
		BWAPI::UnitType m_type;
		BWAPI::Position m_drawPositionTL, m_drawPositionBR, m_textPosition;
		std::string m_name;

		virtual void onFrame_() = 0;

	public:
		static const int boxWidth = 200;
		static const int textHeight = 15;
		static const int boxHeight = 2 * textHeight;

		AUnitSet() {}
		AUnitSet(std::string name, BWAPI::UnitType type) : m_name(name), m_type(type) {}

		void insert(AUnit *unit);
		void removeDead();
		void setDrawPosition(BWAPI::Position p);

		virtual void draw() const;
		virtual void onFrame();
	};


}