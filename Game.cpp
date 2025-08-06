//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Game.hpp"

using Oop::Game;

//------------------------------------------------------------------------------
// static constants used for Game logic
const unsigned int Game::INVALID_SET_INT = 13;
const unsigned int Game::MIN_HANDCARD_PARAMETER = 1;
const unsigned int Game::MAX_HANDCARD_PARAMETER = 7;
const int Game::AMOUNT_OF_PLAYERS = 2;
const int Game::PLAYER_1 = 0;
const int Game::PLAYER_2 = 1;

//------------------------------------------------------------------------------
Game::Game(Interface &io) : io_(io)
{
  im_dead_ = false;
}

//------------------------------------------------------------------------------
Game::~Game() noexcept
{
  for (auto &cards_player1 : card_stack_1)
  {
    delete cards_player1;
  }
  for (auto &cards_player2 : card_stack_2)
  {
    delete cards_player2;
  }
}

//------------------------------------------------------------------------------
bool Game::loadConfig(std::string config_file)
{
  std::ifstream in_file(config_file);
  rapidjson::IStreamWrapper config_stream(in_file);
  rapidjson::Document file;
  file.ParseStream(config_stream);

  //Parsing the config file:
  JsonParser pars;
  if (!pars.parseConfig(file)) //if parseConfig fails we get inside here
  {
    io_.error(Interface::ERROR_INVALID_CONFIG);
    return false;
  }

  //Loading the creatures for 2 Card-Stacks:
  if (!pars.createCards(file, &card_stack_1) || !pars.createCards(file,
      &card_stack_2))
  {
    return false;
  }

  //Check if duplicate cards are valid - only need check for one deck:
  if (!pars.val_duplicates(card_stack_1))
  {
    io_.error(Interface::ERROR_INVALID_CONFIG);
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
void Game::run()
{
  // Initialize players
  players[PLAYER_1] = Player();
  players[PLAYER_2] = Player();

  std::vector<Card *> deck0 = card_stack_1;
  std::vector<Card *> deck1 = card_stack_2;
  Random::getInstance().shufflePickupstack(deck0);
  players[PLAYER_1].setPickUpStack(deck0);
  Random::getInstance().shufflePickupstack(deck1);
  players[PLAYER_2].setPickUpStack(deck1);

  players[PLAYER_1].setName(io_.readPlayerName(PLAYER_1));
  players[PLAYER_2].setName(io_.readPlayerName(PLAYER_2));

  //3 cards for every player
  players[PLAYER_1].setHand();
  players[PLAYER_2].setHand();

  setGameRunning(true);
  game_round_counter = PLAYER_1;
  while (game_running_)
  {
    io_.out(Interface::INFO, Interface::INFO_ROUND +
                             std::to_string(game_round_counter));
    active_player_id_ = PLAYER_1;
    player_turn_counter_ = PLAYER_1;
    executePlayerTurns();
    ++game_round_counter;
  }
}

//------------------------------------------------------------------------------
int Game::getInactivePlayerId() const
{
  if (active_player_id_ == PLAYER_1)
  {
    return PLAYER_2;
  }
  else
  {
    return PLAYER_1;
  }
}

//------------------------------------------------------------------------------
void Game::executePlayerTurns()
{
  //Do a turn for for each player:
  while (player_turn_counter_ < AMOUNT_OF_PLAYERS)
  {
    //Each Round, Players get Mana, a Card, and their Creatures Status updates:
    io_.out(Interface::INFO, Interface::INFO_CURRENT_PLAYER +
    players[active_player_id_].getName());
    players[active_player_id_].addMana(game_round_counter);
    if (!players[active_player_id_].pickUpCard())
    {
      im_dead_ = true;
    }
    players[active_player_id_].wakeUp();
    players[active_player_id_].canAttackAgain();

    //Display Gamefield:
    io_.out(&players[active_player_id_], &players[getInactivePlayerId()]);

    //In each active turn, a player can execute multiple commands:
    setTurnActive(true);
    while (isTurnActive())
    {
      checkActiveDeath();
      executeCommands();
      //player_quit_game_ flag to break out after quit:
      if (player_quit_game_)
        break;

      players[getInactivePlayerId()].wakeUpShield();
    }
    player_turn_counter_++;
  }
}

//------------------------------------------------------------------------------
void Game::setPlayerTurnCounter(int player_turn_counter)
{
  player_turn_counter_ = player_turn_counter;
}

//------------------------------------------------------------------------------
void Game::setGameRunning(bool game_running)
{
  game_running_ = game_running;
}

//------------------------------------------------------------------------------
void Game::setPlayerQuitGame(bool player_quit_game)
{
  player_quit_game_ = player_quit_game;
}

//------------------------------------------------------------------------------
Oop::Player *Game::getPlayers()
{
  return players;
}

//------------------------------------------------------------------------------
void Game::makeLower(std::string &command)
{
  for (char &counter : command)
  {
    //iterate every character and make upper case:
    counter = tolower(counter);
  }
}

//------------------------------------------------------------------------------
std::string Game::getInput()
{
  if (im_dead_)
  {
    return Interface::COMMAND_QUIT;
  }
  //print command prompt:
  io_.printCommandPrompt(players[active_player_id_].getName());
  while ((user_input = io_.in()).empty())
  {
    io_.printCommandPrompt(players[active_player_id_].getName());
  }
  return user_input;
}

//------------------------------------------------------------------------------
void Game::setActivePlayerId(int active_player_id)
{
  active_player_id_ = active_player_id;
}

//------------------------------------------------------------------------------
void Game::setTurnActive(bool turnActive)
{
  turn_active = turnActive;
}

//------------------------------------------------------------------------------
bool Game::isTurnActive() const
{
  return turn_active;
}

//------------------------------------------------------------------------------
unsigned int Game::validInt(const std::string &make_int)
{
  std::istringstream stream(make_int);
  unsigned int value = 0;

  // Invalid if stream fails
  if (!(stream >> value))
  {
    return INVALID_SET_INT;
  }
  return value;
}

//------------------------------------------------------------------------------
bool Game::validGameFieldOrHand(unsigned int check_me)
{
  return !(check_me < MIN_HANDCARD_PARAMETER ||
            check_me > MAX_HANDCARD_PARAMETER);
}

//------------------------------------------------------------------------------
bool Game::validAttackInt(unsigned int check_me)
{
  return !(check_me < Command::PLAYER_POSITON ||
            check_me > MAX_HANDCARD_PARAMETER);
}

//------------------------------------------------------------------------------
void Game::killedEnemy(bool no_life)
{
  //Active Player killed enemy player. Inactive player is set up to lose:
  im_dead_ = no_life;
  setActivePlayerId(getInactivePlayerId());
}

//------------------------------------------------------------------------------
void Game::checkActiveDeath()
{
  if (players[active_player_id_].isDead())
  {
    im_dead_ = true;
  }
}

//------------------------------------------------------------------------------
void Game::executeCommands()
{
  std::string command;
  player_quit_game_ = false;
  std::string parameter;
  std::vector<std::string> many_params;
  std::map<std::string, Command *> cmd_map;

  //Read input and process commands:
  user_input = getInput();
  std::stringstream stream(user_input);
  stream >> command;
  makeLower(command);
  //the other words in "stream" will be put into "parameter" vector
  while (stream)
  {
    stream >> parameter;
    many_params.push_back(parameter);
  }
  //check the "command" and create the corresponding pointer
  if (command == Interface::COMMAND_QUIT)
    cmd_map[Interface::COMMAND_QUIT] = new Quit(io_);
  else if (command == Interface::COMMAND_FINISH)
    cmd_map[Interface::COMMAND_FINISH] = new Finish(io_);
  else if (command == Interface::COMMAND_SET)
    cmd_map[Interface::COMMAND_SET] = new SetCard(io_);
  else if (command == Interface::COMMAND_STATE)
    cmd_map[Interface::COMMAND_STATE] = new State(io_);
  else if (command == Interface::COMMAND_HELP)
    cmd_map[Interface::COMMAND_HELP] = new Help(io_);
  else if (command == Interface::COMMAND_ATTACK)
    cmd_map[Interface::COMMAND_ATTACK] = new Attack(io_);
  else if (command == Interface::COMMAND_CAST)
    cmd_map[Interface::COMMAND_CAST] = new Cast(io_);
  else if (command == Interface::COMMAND_SACRIFICE)
    cmd_map[Interface::COMMAND_SACRIFICE] = new Sacrifice(io_);
  else
    io_.out(Interface::INFO, Interface::WARNING_UNKNOWN_COMMAND);

  // execute any command in the cmd_map then delete the object:
  if (!cmd_map.empty())
  {
    cmd_map[command]->execute(*this, many_params);
    delete cmd_map[command];
  }
}

//------------------------------------------------------------------------------
int Game::getActivePlayerId() const
{
  return active_player_id_;
}
