#pragma once
#include "AUnit.hpp"
#include "Formation.hpp"
#include <set>


namespace Amorphis {


	class AUnitSet {
	protected:
		std::vector<AUnit*> m_units;
		BWAPI::UnitType m_type;
		BWAPI::Position m_drawPositionTL, m_drawPositionBR, m_textPosition;
		std::string m_name;
		Formation m_targetFormation;

		virtual void onFrame_() {}

	public:
		static const int boxWidth = 200;
		static const int textHeight = 15;
		static const int boxHeight = 2 * textHeight;

		enum State {
			Idle,
			Attack,
			Move,
			MoveFormation,
			Gather
		} m_state = Idle;
		virtual const char* toString(State state) const;
		State state() const { return m_state; }

		AUnitSet() {}
		AUnitSet(std::string name, BWAPI::UnitType type) : m_name(name), m_type(type) {}

		virtual void addUnit(AUnit *unit);
		virtual void removeUnit(BWAPI::Unit unit);
		virtual void removeUnit(AUnit *unit);
		virtual void removeDead();
		virtual void setDrawPosition(BWAPI::Position p);
		virtual BWAPI::Position center() const;
		BWAPI::UnitType type() const { return m_type;  }

		virtual void draw() const;
		virtual void onFrame();
		virtual void moveFormation(const Formation &f);
		const std::string& name() const { return m_name; }
		const std::vector<AUnit*>& units() const { return m_units; }
	};


}