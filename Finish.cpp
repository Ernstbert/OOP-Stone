//------------------------------------------------------------------------------
// Finish.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Finish.hpp"

using Oop::Finish;

//------------------------------------------------------------------------------
Finish::Finish(Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Finish::~Finish() noexcept
{
}

//------------------------------------------------------------------------------
void Finish::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 1)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }

  //switch player
  if (gamefield.getActivePlayerId() == 0)
  {
    gamefield.setActivePlayerId(1);
  }
  else
  {
    gamefield.setActivePlayerId(0);
  }

  gamefield.getPlayers()[gamefield.getActivePlayerId()].wakeUp();
  gamefield.getPlayers()[gamefield.getActivePlayerId()].canAttackAgain();

  gamefield.setTurnActive(false);
}
