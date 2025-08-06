//------------------------------------------------------------------------------
// SpellCard.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "SpellCard.hpp"

using Oop::SpellCard;

//------------------------------------------------------------------------------
SpellCard::SpellCard(SpellType type) : Card(Interface::STRING_HEALER, 0, SPELL),
                                       spell_type_(type)
{
  switch (type)
  {
    case HEALER:
      setName(Interface::STRING_HEALER);
      setManaCost(HEALER_COST);
      break;
    case RELIEF:
      setName(Interface::STRING_RELIEF);
      setManaCost(RELIEF_COST);
      break;
    case REBIRTH:
      setName(Interface::STRING_REBIRTH);
      setManaCost(REBIRTH_COST);
      break;
    case DRACULA:
      setName(Interface::STRING_DRACULA);
      setManaCost(DRACULA_COST);
      break;
    default:
      setName(Interface::STRING_HEALER);
      setManaCost(HEALER_COST);
      break;
  }
}

//------------------------------------------------------------------------------
SpellCard::~SpellCard() noexcept
{
}

//------------------------------------------------------------------------------
SpellCard::SpellType SpellCard::getSpellType() const
{
  return spell_type_;
}


