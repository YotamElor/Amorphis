#pragma once


namespace Amorphis {


	class DisplaySettings{
	public:
		static const bool DisplayOn = true;
		static const bool UnitName = DisplayOn && true;
		static const bool AUnitSetBox = DisplayOn && true;
		static const bool Target = DisplayOn && true;
		static const bool MoveTarget = DisplayOn && true;
		static const bool UnitsManager = DisplayOn && true;
		static const bool Strategy = DisplayOn && true;
		static const bool Map = DisplayOn && true;
	};


	class LogSettings {
	public:
		static const bool LogOn = true;
		static const bool LogUnitSetMove = LogOn && true;
	};

}