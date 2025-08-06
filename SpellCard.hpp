//------------------------------------------------------------------------------
// SpellCard.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef SPELLCARD_HPP
#define SPELLCARD_HPP

#include "Card.hpp"

namespace Oop
{
  class SpellCard : public Card
  {
    public:

      enum SpellType
      {
        HEALER, RELIEF, REBIRTH, DRACULA
      };

    private:

      //Attributes:
      const SpellType spell_type_;

    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      SpellCard(SpellType type);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      SpellCard(const SpellCard &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      SpellCard &operator = (const SpellCard &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~SpellCard() noexcept;

      //------------------------------------------------------------------------
      // The getSpellType method
      //
      SpellType getSpellType() const;

  };
}

#endif //SPELLCARD_HPP
