//------------------------------------------------------------------------------
// Help.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef HELP_HPP
#define HELP_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class Help : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Help(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Help(const Help &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Help &operator = (const Help &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Help() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //HELP_HPP
