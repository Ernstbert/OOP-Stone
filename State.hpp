//------------------------------------------------------------------------------
// State.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef STATE_HPP
#define STATE_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class State : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      State(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      State(const State &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      State &operator = (const State &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~State() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //STATE_HPP
