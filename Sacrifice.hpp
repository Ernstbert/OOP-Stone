//------------------------------------------------------------------------------
// Sacrifice.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef SACRIFICE_HPP
#define SACRIFICE_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class Sacrifice : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Sacrifice(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Sacrifice(const Sacrifice &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Sacrifice &operator = (const Sacrifice &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Sacrifice() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //SACRIFICE_HPP
