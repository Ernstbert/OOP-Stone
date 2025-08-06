//------------------------------------------------------------------------------
// Cast.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Cast.hpp"

using Oop::Cast;

//------------------------------------------------------------------------------
Cast::Cast(Oop::Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Cast::~Cast() noexcept
{
}

//------------------------------------------------------------------------------
void Cast::execute(Oop::Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 2)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }
  unsigned int my_spell = gamefield.validInt(params.at(0));
  unsigned int handsize;
  Player *gamer = &gamefield.getPlayers()[gamefield.getActivePlayerId()];
  Player *enemy = &gamefield.getPlayers()[gamefield.getInactivePlayerId()];
  std::vector<Card *> card_type;
  SpellCard::SpellType some_type;

  if (!gamefield.validGameFieldOrHand(my_spell))
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return;
  }

  card_type = gamer->getHandCards();
  handsize = card_type.size();

  if (my_spell > handsize || card_type[my_spell - Command::VECTOR_OFFSET]->
  getType() != Card::CardType::SPELL ||
  card_type[my_spell - Command::VECTOR_OFFSET] == nullptr)
  {
    io_over_cmd_.out(Interface::INFO,
        Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }
  my_spell -= Command::VECTOR_OFFSET;

  if (!gamer->checkMana(my_spell))
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_NOT_ENOUGH_MANA);
    return;
  }

  //Cast specific Spell:
  some_type = gamer->getSpell(my_spell);
  switch (some_type)
  {
    case SpellCard::HEALER:
      gamer->healCreatures();
      break;
    case SpellCard::RELIEF:
      gamer->reliefYourself();
      break;
    case SpellCard::REBIRTH:
      if (gamer->getGraveyard().empty())
        io_over_cmd_.out(Interface::INFO,
            Interface::WARNING_REBIRTH_UNSUCCESSFUL);
      else
        gamer->respawnCreature();
      break;
    case SpellCard::DRACULA:
      if (!enemy->reduceLifePoints(2))
        gamefield.killedEnemy(true);
      gamer->addLifePoints(2);
      break;
    default:
      io_over_cmd_.out(Interface::INFO,
          Interface::WARNING_REBIRTH_UNSUCCESSFUL);
  }
}
