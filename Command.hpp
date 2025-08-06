//------------------------------------------------------------------------------
// Command.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

namespace Oop
{
  class Game;

  class Interface;

  class Command
  {
    protected:
      Interface &io_over_cmd_;

    public:
      //------------------------------------------------------------------------
      // Constants
      // Fixed values used in Commands
      //
      const static unsigned int VECTOR_OFFSET;
      const static unsigned int PLAYER_POSITON;
      const static unsigned int EXECUTION_IMPOSSIBLE;
      const static int SACRIFICE_GAIN;

      static const std::string ATTACK_PREPOSITION;
      static const std::string SET_PREPOSITION;

      //------------------------------------------------------------------------
      // Constructor
      //
      Command(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Command(const Command &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Command &operator = (const Command &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Command() noexcept;

      //------------------------------------------------------------------------
      // The virtual execute method
      //
      virtual void execute(Game &gamefield, std::vector<std::string> &params)=0;
  };
}

#endif //COMMAND_HPP
