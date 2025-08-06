//------------------------------------------------------------------------------
// Game.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef GAME_HPP
#define GAME_HPP

#include "Quit.hpp"
#include "Finish.hpp"
#include "SetCard.hpp"
#include "State.hpp"
#include "Help.hpp"
#include "Attack.hpp"
#include "Cast.hpp"
#include "Sacrifice.hpp"
#include "Player.hpp"
#include "Random.hpp"
#include "JsonParser.hpp"

#include <sstream>

//------------------------------------------------------------------------------
namespace Oop
{
  class JsonParser;

  class Interface;

  class Card;

  class Command;

  //----------------------------------------------------------------------------
  // Game Class
  // This class starts the game and executes game rounds/ player turns
  //
  class Game
  {
    private:

      //------------------------------------------------------------------------
      // Reference to the Interface
      //
      Interface &io_;

      //------------------------------------------------------------------------
      // Integer holding the current active player ID
      //
      int active_player_id_;

      //------------------------------------------------------------------------
      // Holds true if game is running, else false
      //
      bool game_running_;

      //------------------------------------------------------------------------
      // Integer counting the played rounds
      //
      int game_round_counter;

      //------------------------------------------------------------------------
      // Integer counting the played turns per round
      //
      int player_turn_counter_;

      //------------------------------------------------------------------------
      // Holds information if the active player quit the game or not
      //
      bool player_quit_game_;

      //------------------------------------------------------------------------
      // Bool if the players turn is still active
      //
      bool turn_active;

      //------------------------------------------------------------------------
      // Bool evaluating to true if the inactive player loses the game
      //
      bool im_dead_;

      //------------------------------------------------------------------------
      // Player objects are owned by Game, and are stored in this Player-Array
      //
      Player players[2];

      //------------------------------------------------------------------------
      // Holds user input string
      //
      std::string user_input;

      //------------------------------------------------------------------------
      // The sorted and validified card stack 1 and 2, holding the Card-Objects
      // for the game's lifetime for player 1 and 2
      //
      std::vector<Card *> card_stack_1;
      std::vector<Card *> card_stack_2;

    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Game(Interface &io);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Game(const Game &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Game &operator = (const Game &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Game() noexcept;

      //------------------------------------------------------------------------
      // Constants
      // Fixed values throughout the game, not found or fitting from Interface
      //
      const static unsigned int INVALID_SET_INT;
      const static unsigned int MIN_HANDCARD_PARAMETER;
      const static unsigned int MAX_HANDCARD_PARAMETER;
      const static int AMOUNT_OF_PLAYERS;
      const static int PLAYER_1;
      const static int PLAYER_2;

      //------------------------------------------------------------------------
      // METHODS
      //
      //------------------------------------------------------------------------
      // The loadConfig function
      // Loads the config file (and checks for errors)
      // @param std::string config_file name
      // @return bool loaded successfully or not
      //
      bool loadConfig(std::string config_file);

      //------------------------------------------------------------------------
      // The run function
      // Runs the main game
      // @return void
      //
      void run();

      //------------------------------------------------------------------------
      // The getActivePlayerId function
      // Gets the ID of the currently active player
      // @return int ID of active player
      //
      int getActivePlayerId() const;

      //------------------------------------------------------------------------
      // The getInactivePlayerId function
      // Gets the ID of the currently inactive player
      // @return int ID of inactive player
      //
      int getInactivePlayerId() const;

      Player *getPlayers();

      //------------------------------------------------------------------------
      // SETTER
      //
      void setPlayerTurnCounter(int player_turn_counter);

      void setGameRunning(bool game_running);

      void setPlayerQuitGame(bool player_quit_game);

      void setActivePlayerId(int active_player_id);

      void setTurnActive(bool turnActive);

      //------------------------------------------------------------------------
      // The isTurnActive function
      // Checks if the turn is active
      //
      bool isTurnActive() const;

      //------------------------------------------------------------------------
      // The killedEnemy function
      //
      void killedEnemy(bool no_life);

      //------------------------------------------------------------------------
      // The validInt function
      //
      unsigned int validInt(const std::string &make_int);

      //------------------------------------------------------------------------
      // The executePlayerTurns function
      // Executes a game round, incl. 2 player turns
      // @param Player -> ptr-array with both players
      // @return void
      //
      void executePlayerTurns();

      //------------------------------------------------------------------------
      // The makeLower function
      // Makes characters lower case
      //
      void makeLower(std::string &command);

      //------------------------------------------------------------------------
      // The getInput function
      //
      std::string getInput();

      //------------------------------------------------------------------------
      // The validGameFieldOrHand function
      //
      bool validGameFieldOrHand(unsigned int check_me);

      //------------------------------------------------------------------------
      // The validAttackInt function
      //
      bool validAttackInt(unsigned int check_me);

      void checkActiveDeath();

      void executeCommands();
  };
}

#endif //GAME_HPP
