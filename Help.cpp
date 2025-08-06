//------------------------------------------------------------------------------
// Help.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Help.hpp"

using Oop::Help;

//------------------------------------------------------------------------------
Help::Help(Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Help::~Help() noexcept
{
}

//------------------------------------------------------------------------------
void Help::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 1)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }
  for (auto &help : Interface::INFO_HELP_MSGS)
  {
    io_over_cmd_.out(Interface::INFO, help);
  }
}
