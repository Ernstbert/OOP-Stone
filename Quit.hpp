//------------------------------------------------------------------------------
// Quit.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef QUIT_HPP
#define QUIT_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class Quit : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Quit(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Quit(const Quit &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Quit &operator = (const Quit &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Quit() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //QUIT_HPP
