#include "AmorphisAIModule.h"
#include <iostream>
#include "Utils/Logger.hpp"
#include "bwem/bwem.h"


using namespace BWAPI;
using namespace Filter;
using namespace Amorphis;
using namespace std;
namespace { auto & theMap = BWEM::Map::Instance(); }


void AmorphisAIModule::onStart()
{
	Logger::getInstance()->init();
	ALOG("The map is " + Broodwar->mapName());

	Broodwar << "Map initialization..." << std::endl;
	amorphisMain = new Amorphis::AmorphisMain();

	theMap.Initialize();
	theMap.EnableAutomaticPathAnalysis();
	bool startingLocationsOK = theMap.FindBasesForStartingLocations();
	assert(startingLocationsOK);

	// Enable the UserInput flag, which allows us to control the bot and type messages.
	Broodwar->enableFlag(Flag::UserInput);

	// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	//Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Set the command optimization level so that common commands can be grouped
	// and reduce the bot's APM (Actions Per Minute).
	Broodwar->setCommandOptimizationLevel(2);

//	if (Broodwar->enemy()) {
//		ALOG("The matchup is " + Broodwar->self()->getRace().c_str() + " vs " + Broodwar->enemy()->getRace().c_str());
//	}
}

void AmorphisAIModule::onEnd(bool isWinner)
{
  // Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void AmorphisAIModule::onFrame()
{
	// Called once every game frame

	// Display the game frame rate as text in the upper left area of the screen
	try
	{
		Broodwar->drawTextScreen(0, 0, "FPS: %d (%.1f)", Broodwar->getFPS(), Broodwar->getAverageFPS());
		amorphisMain->draw();
	}
	catch (const std::exception & e)
	{
		AERR(string("EXCEPTION: ") + string(e.what()));
	}

	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	try
	{
		amorphisMain->onFrame();
	}
	catch (const std::exception & e)
	{
		AERR(string("EXCEPTION: ") + string(e.what()));
	}
}

void AmorphisAIModule::onSendText(std::string text)
{

  // Send the text to the game if it is not being processed.
  Broodwar->sendText("%s", text.c_str());


  // Make sure to use %s and pass the text as a parameter,
  // otherwise you may run into problems when you use the %(percent) character!

}

void AmorphisAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
  // Parse the received text
  Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void AmorphisAIModule::onPlayerLeft(BWAPI::Player player)
{
  // Interact verbally with the other players in the game by
  // announcing that the other player has left.
  Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void AmorphisAIModule::onNukeDetect(BWAPI::Position target)
{

  // Check if the target is a valid position
  if ( target )
  {
    // if so, print the location of the nuclear strike target
    Broodwar << "Nuclear Launch Detected at " << target << std::endl;
  }
  else 
  {
    // Otherwise, ask other players where the nuke is!
    Broodwar->sendText("Where's the nuke?");
  }

  // You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void AmorphisAIModule::onUnitDiscover(BWAPI::Unit unit)
{
	amorphisMain->onUnitDiscover(unit);
}

void AmorphisAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onUnitCreate(BWAPI::Unit unit)
{
//	m_unitsManager.onUnitDiscover(unit);
}

void AmorphisAIModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onUnitMorph(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void AmorphisAIModule::onSaveGame(std::string gameName)
{
  Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void AmorphisAIModule::onUnitComplete(BWAPI::Unit unit)
{
}
