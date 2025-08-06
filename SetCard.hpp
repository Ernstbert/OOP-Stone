//------------------------------------------------------------------------------
// SetCard.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef SETCARD_HPP
#define SETCARD_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class SetCard : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      SetCard(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      SetCard(const SetCard &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      SetCard &operator = (const SetCard &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~SetCard() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);
  };
}

#endif //SETCARD_HPP
