//------------------------------------------------------------------------------
// CreatureCard.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "CreatureCard.hpp"

using Oop::CreatureCard;

//------------------------------------------------------------------------------
CreatureCard::CreatureCard(std::string name,
                           int mana_cost,
                           int damage_points,
                           int life_points,
                           bool shield,
                           bool mana_drain,
                           bool speedy) :
    Card(name, mana_cost, CREATURE),
    damage_points_(damage_points), life_points_(life_points),
    shield_(shield), mana_drain_(mana_drain),
    ready_to_fight_(false),
    already_attacked_(false), speedy_(speedy)
{
  current_life_points_ = life_points_;
  if (speedy_)
  {
    sleepy_counter_ = SLEEP_ROUNDS;
    ready_to_fight_ = true;
  }
  sleepy_counter_ = 0;
  can_attack_in_x_turns_ = 0;
}

//------------------------------------------------------------------------------
CreatureCard::~CreatureCard() noexcept
{
}

//------------------------------------------------------------------------------
int CreatureCard::getDamagePoints() const
{
  return damage_points_;
}

//------------------------------------------------------------------------------
int CreatureCard::getLifePoints() const
{
  return life_points_;
}

//------------------------------------------------------------------------------
int CreatureCard::getCurrentLifePoints() const
{
  return current_life_points_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getShield() const
{
  return shield_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getManaDrain() const
{
  return mana_drain_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getReadyToFight() const
{
  return ready_to_fight_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getAlreadyAttacked() const
{
  return already_attacked_;
}

//------------------------------------------------------------------------------
bool CreatureCard::getSpeedy() const
{
  return speedy_;
}

//------------------------------------------------------------------------------
void CreatureCard::setCurrentLifePoints(int current_life_points)
{
  current_life_points_ = current_life_points;
}

//------------------------------------------------------------------------------
void CreatureCard::setReadyToFight(bool ready_to_fight)
{
  ready_to_fight_ = ready_to_fight;
}

//------------------------------------------------------------------------------
void CreatureCard::setAlreadyAttacked(bool already_attacked)
{
  already_attacked_ = already_attacked;
}

//------------------------------------------------------------------------------
void CreatureCard::sleepyCount()
{
  sleepy_counter_++;
}

//------------------------------------------------------------------------------
int CreatureCard::getSleepyCounter() const
{
  return sleepy_counter_;
}

//------------------------------------------------------------------------------
int CreatureCard::getAttackAgain() const
{
  return can_attack_in_x_turns_;
}

//------------------------------------------------------------------------------
void CreatureCard::attackAgainCount()
{
  can_attack_in_x_turns_++;
}

