//------------------------------------------------------------------------------
// Attack.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef ATTACK_HPP
#define ATTACK_HPP

#include "Game.hpp"
#include "Command.hpp"

namespace Oop
{
  class Player;

  class CreatureCard;

  class Attack : public Command
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Attack(Interface &io_over_cmd);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Attack(const Attack &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Attack &operator = (const Attack &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Attack() noexcept;

      //------------------------------------------------------------------------
      // The execute method
      //
      void execute(Game &gamefield, std::vector<std::string> &params);

      //------------------------------------------------------------------------
      // The attackCreature method
      //
      void attackCreature(unsigned int opponent_position,
                          unsigned int friendly_position, Player *gamer, Player
              *enemy_gamer);

      //------------------------------------------------------------------------
      // The attackPlayer method
      //
      void attackPlayer(Game &gamefield, unsigned int friendly_position,
          Player *gamer, Player *enemy_gamer);

      //------------------------------------------------------------------------
      // The validCreatureAttack method
      //
      bool validCreatureAttack(unsigned int friendly_position,
          unsigned int opponent_position, Player *gamer, Player *enemy_gamer);

      //------------------------------------------------------------------------
      // The validPlayerAttack method
      //
      bool validPlayerAttack(unsigned int friendly_position, Player *gamer);

      //------------------------------------------------------------------------
      // The checkEnemyShield method
      // Checks if the enemy gamefield has shield-creatures on it
      // @param enemy the enemy gamefield which is checked for shields
      // @return bool true if shields are present or false if not
      //
      bool checkEnemyShield(const CreatureCard *const *enemy);
  };
}

#endif //ATTACK_HPP
