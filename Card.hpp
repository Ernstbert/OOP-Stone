//------------------------------------------------------------------------------
// Card.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef CARD_HPP
#define CARD_HPP

#include "Interface.hpp"

namespace Oop
{
  class Game;

  class Card
  {
    public:
      enum CardType
      {
        CREATURE, SPELL
      };

    protected:

      std::string name_;
      int mana_cost_;

    private:

      CardType type_;

    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Card();

      //------------------------------------------------------------------------
      // Special constructor
      //
      Card(std::string name, int mana_cost, CardType type);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Card(const Card &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Card &operator = (const Card &original) = delete;


      //------------------------------------------------------------------------
      // Pure virtual Destructor
      //
      virtual ~Card() noexcept = 0;

      //------------------------------------------------------------------------
      // Constants
      // Fixed values throughout the game, used for Cards
      //
      const static int CREATURE_MAX_LIFE;
      const static int CREATURE_HEAL;
      const static int SLEEP_ROUNDS;
      const static int MIN_PLAYER_LIFE;
      const static int PICK_UP_FAIL_LIFE_LOSS;
      const static int START_MANA;
      const static int MANA_GAIN_FACTOR;
      const static int START_CARDS_AMAOUNT;

      //------------------------------------------------------------------------
      // Fixed values of spell manacosts:
      const static int HEALER_COST;
      static const int RELIEF_COST;
      static const int REBIRTH_COST;
      static const int DRACULA_COST;

      //------------------------------------------------------------------------
      // GETTER
      //
      std::string getName() const;
      CardType getType() const;
      int getManaCost() const;

      //------------------------------------------------------------------------
      // SETTER
      //
      void setName(const std::string &name);
      void setManaCost(int mana_cost);
  };
}
#endif //CARD_HPP

