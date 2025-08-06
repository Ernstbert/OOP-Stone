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

#include "SetCard.hpp"

using Oop::SetCard;

//------------------------------------------------------------------------------
SetCard::SetCard(Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
SetCard::~SetCard() noexcept
{
}

//------------------------------------------------------------------------------
void SetCard::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 4)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }

  unsigned int hand_position = gamefield.validInt(params.at(0));
  std::string preposition = params.at(1);
  unsigned int field_position = gamefield.validInt(params.at(2));
  Player *gamer = &gamefield.getPlayers()[gamefield.getActivePlayerId()];

  std::vector<Card *> card_type;
  const CreatureCard *const *position;
  unsigned int handsize;

  //Check if parameters are allowed:
  if (!gamefield.validGameFieldOrHand(hand_position) ||
      !gamefield.validGameFieldOrHand(field_position) ||
      preposition != Command::SET_PREPOSITION)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return;
  }

  handsize = gamer->getHandCards().size();
  card_type = gamer->getHandCards();
  position = gamer->getGameField();

  //Check if command can be executed:
  if (hand_position > handsize || card_type[hand_position - 1]->getType() !=
          Card::CardType::CREATURE || position[field_position - 1] != nullptr)
  {
    io_over_cmd_.out(Interface::INFO,
                     Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }

  if (!gamer->checkMana(hand_position - 1))
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_NOT_ENOUGH_MANA);
    return;
  }
  gamer->setCard(hand_position - 1, field_position - 1);

}
