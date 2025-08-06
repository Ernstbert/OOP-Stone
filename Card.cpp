//------------------------------------------------------------------------------
// Card.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Card.hpp"

using Oop::Card;

//------------------------------------------------------------------------------
// Fixed values throughout the game, used for Cards and Players
//
const int Card::CREATURE_MAX_LIFE = 9;
const int Card::CREATURE_HEAL = 1;
const int Card::SLEEP_ROUNDS = 1;
const int Card::MIN_PLAYER_LIFE = 1;
const int Card::PICK_UP_FAIL_LIFE_LOSS = 1;
const int Card::START_MANA = 1;
const int Card::MANA_GAIN_FACTOR = 2;
const int Card::START_CARDS_AMAOUNT = 3;

// Fixed Values of spell manacosts
const int Card::HEALER_COST = 5;
const int Card::RELIEF_COST = 3;
const int Card::REBIRTH_COST = 5;
const int Card::DRACULA_COST = 2;

//------------------------------------------------------------------------------
Card::Card() = default;

//------------------------------------------------------------------------------
Card::Card(std::string name, int mana_cost, Card::CardType type)
    : name_(name), mana_cost_(mana_cost), type_(type)
{
}

//------------------------------------------------------------------------------
Card::~Card() noexcept
{
}

//------------------------------------------------------------------------------
std::string Card::getName() const
{
  return name_;
}

//------------------------------------------------------------------------------
Card::CardType Card::getType() const
{
  return type_;
}

//------------------------------------------------------------------------------
int Card::getManaCost() const
{
  return mana_cost_;
}

//------------------------------------------------------------------------------
void Card::setName(const std::string &name)
{
  name_ = name;
}

//------------------------------------------------------------------------------
void Card::setManaCost(int mana_cost)
{
  mana_cost_ = mana_cost;
}

