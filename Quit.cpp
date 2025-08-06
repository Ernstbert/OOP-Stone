//------------------------------------------------------------------------------
// Quit.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Quit.hpp"

using Oop::Quit;

//------------------------------------------------------------------------------
Quit::Quit(Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Quit::~Quit() noexcept
{
}

//------------------------------------------------------------------------------
void Quit::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 1)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }

  io_over_cmd_.out(Interface::INFO, Interface::ENDLINE_PART_ONE +
    gamefield.getPlayers()[gamefield.getInactivePlayerId()].getName() +
    Interface::ENDLINE_PART_TWO);
  gamefield.setPlayerTurnCounter(2);
  gamefield.setPlayerQuitGame(true);
  gamefield.setGameRunning(false);
}
