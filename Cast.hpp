//------------------------------------------------------------------------------
// Cast.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef CAST_HPP
#define CAST_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class Cast : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Cast(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Cast(const Cast &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Cast &operator = (const Cast &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Cast() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //CAST_HPP
