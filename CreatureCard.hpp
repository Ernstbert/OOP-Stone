//------------------------------------------------------------------------------
// CreatureCard.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef CREATURECARD_HPP
#define CREATURECARD_HPP

#include "Card.hpp"

namespace Oop
{
  class CreatureCard : public Card
  {
    private: //TODO: COMMENT EVERY VARIABLE -.-
      //Attributes:
      const int damage_points_;
      const int life_points_;
      int current_life_points_;
      const bool shield_;
      bool mana_drain_;
      bool ready_to_fight_;
      bool already_attacked_;
      bool speedy_ = false;
      int sleepy_counter_;
      int can_attack_in_x_turns_;

    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      CreatureCard(std::string name, int mana_cost, int damage_points,
                   int life_points, bool shield, bool mana_drain, bool speedy);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      CreatureCard(const CreatureCard &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      CreatureCard &operator = (const CreatureCard &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      ~CreatureCard() noexcept;

      //------------------------------------------------------------------------
      // GETTER
      //
      int getDamagePoints() const;
      int getLifePoints() const;
      int getCurrentLifePoints() const;
      bool getShield() const;
      bool getManaDrain() const;
      bool getReadyToFight() const;
      bool getAlreadyAttacked() const;
      bool getSpeedy() const;
      int getSleepyCounter() const;
      int getAttackAgain() const;

      //------------------------------------------------------------------------
      // SETTER
      //
      void setCurrentLifePoints(int current_life_points);
      void setReadyToFight(bool ready_to_fight);
      void setAlreadyAttacked(bool already_attacked);

      //------------------------------------------------------------------------
      // The sleepyCount method
      // Increases the sleepy_counter_ by 1. Used to count individual sleep time
      //
      void sleepyCount();

      //------------------------------------------------------------------------
      // The attackAgainCount method
      // Increases can_attack_in_x_turns_ by 1. Used to count when individual
      // creature can attack again
      //
      void attackAgainCount();

  };
}

#endif //CREATURECARD_HPP
