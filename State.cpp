//------------------------------------------------------------------------------
// State.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "State.hpp"

using Oop::State;

//------------------------------------------------------------------------------
State::State(Oop::Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
State::~State() noexcept
{
}

//------------------------------------------------------------------------------
void State::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 1)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }
  io_over_cmd_.out(&gamefield.getPlayers()[gamefield.getActivePlayerId()],
                   &gamefield.getPlayers()[gamefield.getInactivePlayerId()]);
}
