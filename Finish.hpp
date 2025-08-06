//------------------------------------------------------------------------------
// Finish.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef FINISH_HPP
#define FINISH_HPP

#include "Command.hpp"
#include "Game.hpp"

namespace Oop
{
  class Finish : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      Finish(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Finish(const Finish &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Finish &operator = (const Finish &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Finish() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);

  };
}

#endif //FINISH_HPP
