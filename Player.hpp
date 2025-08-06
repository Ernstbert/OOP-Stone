//------------------------------------------------------------------------------
// Player.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef PLAYER_H
#define PLAYER_H

#include "CreatureCard.hpp"
#include "SpellCard.hpp"

//------------------------------------------------------------------------------
namespace Oop
{

  class Interface;

  class Card;

  //----------------------------------------------------------------------------
  // Game Player
  // This class holds all valuable player information,
  // including cards, life- & manapoints
  //
  class Player
  {
    private:

      //------------------------------------------------------------------------
      // Holding the players name
      //
      std::string name_;

      //------------------------------------------------------------------------
      // Holding the players life
      //
      int life_points_;

      //------------------------------------------------------------------------
      // Holding the players mana
      //
      int mana_points_;

      //------------------------------------------------------------------------
      // The gamefield with a fixed size of 7, holding CreatureCard pointers
      //
      CreatureCard *game_field_[Interface::NUM_OF_GAMEFIELD_CARDS] = {};

      //------------------------------------------------------------------------
      // Stores the players full card deck
      //
      std::vector<Card *> pick_up_stack_;

      //------------------------------------------------------------------------
      // Stores the players hand cards
      //
      std::vector<Card *> hand_;

      //------------------------------------------------------------------------
      // Stores the dead creatures
      //
      std::vector<CreatureCard *> graveyard_;

      //------------------------------------------------------------------------
      // Stores if this player is dead or not
      //
      bool is_dead_;

      //------------------------------------------------------------------------
      // Special constructor - private because it's unused so far. //TODO
      // @param std::string player name
      //
      Player(std::string name);

    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Player();

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Player() noexcept;

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Player(const Player &original) = delete;

      //------------------------------------------------------------------------
      // Assignment operator
      // Used to assign a Player to the Player-Array owned by Game class
      // @param original Original object to copy.
      Player &operator = (const Player &original);

      //------------------------------------------------------------------------
      // The setPickUpStack method
      // Puts the shuffled card deck from Game.cpp into Players pick_up_stack_
      // @param card_stack the shuffled card stack
      //
      void setPickUpStack(const std::vector<Card *> &card_stack);

      //------------------------------------------------------------------------
      // The setHand function
      // Sets the Player up with 3 Handcards from his cardstack. Only used
      // at the beginning of the game.
      //
      void setHand();

      //------------------------------------------------------------------------
      // The pick up card function
      // Picks up a single card from the cardstack. Used throughout the game.
      //
      bool pickUpCard();

      //------------------------------------------------------------------------
      // The set Card function
      // Used by the SetCard class to set a card from the hand_ onto the 
      // game_field_
      // @param hand_position the position on the hand
      // @param field_position the position on the field
      //
      void setCard(unsigned int hand_position, unsigned int field_position);

      //------------------------------------------------------------------------
      // The setAttacked function
      // Sets the status already_attacked_ to true after a creature attacked
      // @param position the position of the creature that attacked
      //
      void setAttacked(unsigned int position);

      //------------------------------------------------------------------------
      // The addLifePoints function
      // Adds points to player's life points
      // @param int points the amount of life to add
      // @return void
      //
      void addLifePoints(int points);

      //------------------------------------------------------------------------
      // The reduceLifePoints function
      // Reduces the player's life points
      // @param int points the amount of life to reduce
      // @return bool false if player should die from this
      //
      bool reduceLifePoints(int points);

      //------------------------------------------------------------------------
      // The addMana function
      // Adds points to player's mana points
      // @param int points
      //
      void addMana(int Mana);

      //------------------------------------------------------------------------
      // The reduceMana function
      // Reduces player's mana points
      // @param int points
      //
      void reduceMana(int mana);

      //------------------------------------------------------------------------
      // The wakeUp function
      // Wakes up sleeping non-shield-creatures (sets ready_to_fight_ = true)
      //
      void wakeUp();

      //------------------------------------------------------------------------
      // The wakeUpShield function
      // Wakes up sleeping shield-creatures (sets ready_to_fight_ = true)
      //
      void wakeUpShield();

      //------------------------------------------------------------------------
      // The canAttackAgain function
      // Lets creatures attack again in the next round
      //
      void canAttackAgain();

      //------------------------------------------------------------------------
      // The checkMana function
      // Removes mana from player if possible, depending on the cards mana cost.
      // @param hand_position the position of the hand card
      //
      bool checkMana(unsigned int hand_position);

      //------------------------------------------------------------------------
      // The gotAttacked function
      // Handles the players creature life/existance on the gamefield after 
      // an attack from the enemy.
      // @param attacked_position the position of the creature being attacked
      // @param damage the amount of damage from the attacking creature
      //
      void gotAttacked(unsigned int attacked_position, int damage);

      //------------------------------------------------------------------------
      // The attackOnPlayer function
      // Handles the event of life loss on the player.
      // @param damage the damage from the opponent creature
      //
      void attackOnPlayer(int damage);

      //------------------------------------------------------------------------
      // The sacrificeCard function
      // Used by the Sacrifice class. Sacrifices a spell or creature.
      // @param hand_position the card position on the players hand
      // @param type the card type to be sacrificed
      //
      void sacrificeCard(unsigned int hand_position, Card::CardType type);

      //------------------------------------------------------------------------
      // The getSpell function
      // Used by the Cast class to get the SpellType which is being cast.
      // @param spell_position the SpellCards position on the players hand
      // @return SpellCard::SpellType containing the spells spelltype
      //
      SpellCard::SpellType getSpell(unsigned int spell_position);

      //------------------------------------------------------------------------
      // The healCreatures function
      // Used by the Cast class, to cast the "Healer" spellcard. Heals all
      // creatures on friendly field by +1 life.
      //
      void healCreatures();

      //------------------------------------------------------------------------
      // The reliefYourself function
      // Used by the Cast class, to cast the "Relief" spell. Lets the player
      // pick up 3 cards.
      //
      void reliefYourself();

      //------------------------------------------------------------------------
      // The respawnCreature function
      // Used by the Cast class, to cast the "Rebirth" spell. Puts a dead
      // creature from the graveyard back onto the gamefield.
      //
      void respawnCreature();

      //------------------------------------------------------------------------
      // Getter Methods
      //
      std::string getName() const;
      int getLifePoints() const;
      int getManaPoints() const;
      std::vector<Card *> getHandCards() const;
      int getHandSize() const;
      const CreatureCard *const *getGameField() const;
      bool isDead() const;
      std::vector<CreatureCard *> getGraveyard() const;

      //------------------------------------------------------------------------
      // Setter Methods
      //
      void setName(std::string player_name_);
      void setDead(bool dead);
  };
}

#endif
