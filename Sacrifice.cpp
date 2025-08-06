//------------------------------------------------------------------------------
// Sacrifice.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Sacrifice.hpp"

using Oop::Sacrifice;

//------------------------------------------------------------------------------
Sacrifice::Sacrifice(Oop::Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Sacrifice::~Sacrifice() noexcept
{
}

//------------------------------------------------------------------------------
void Sacrifice::execute(Oop::Game &gamefield,
                             std::vector<std::string> &params)
{
  if (params.size() != 2)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }
  unsigned int hand_position = gamefield.validInt(params.at(0));

  Player *gamer = &gamefield.getPlayers()[gamefield.getActivePlayerId()];
  std::vector<Card *> card_type;

  if (!gamefield.validGameFieldOrHand(hand_position))
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return;
  }

  //Check if command can be executed:
  card_type = gamer->getHandCards();
  if (hand_position > card_type.size())
  {
    io_over_cmd_.out(Interface::INFO,
                     Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }
  hand_position -= Command::VECTOR_OFFSET;

  // Sacrifice card:
  Card::CardType spell_or_creature = card_type[hand_position]->getType();
  gamer->sacrificeCard(hand_position, spell_or_creature);

  //Now gain +1 Life for the sacrifice:
  gamer->addLifePoints(Command::SACRIFICE_GAIN);
}
