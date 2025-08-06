//------------------------------------------------------------------------------
// Attack.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//
#include "Attack.hpp"

//TODO: check for unused <iostream> includes everywhere
//TODO: make more? constants?
//TODO: finish Commentheaders for Functions, classes

using Oop::Attack;

//------------------------------------------------------------------------------
Attack::Attack(Oop::Interface &io_over_cmd) : Command(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Attack::~Attack() noexcept
{
}

//------------------------------------------------------------------------------
void Attack::execute(Game &gamefield, std::vector<std::string> &params)
{
  if (params.size() != 4)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAM_COUNT);
    return;
  }

  unsigned int enemy_position = gamefield.validInt(params.at(0));
  std::string preposition = params.at(1);
  unsigned int attacker_position = gamefield.validInt(params.at(2));
  Player *gamer = &gamefield.getPlayers()[gamefield.getActivePlayerId()];
  Player *enemy_gamer = &gamefield.getPlayers()
      [gamefield.getInactivePlayerId()];
  bool has_shields = false;
  unsigned int shield_position = Command::EXECUTION_IMPOSSIBLE;
  const CreatureCard *const *enemy = enemy_gamer->getGameField();

  //Check for valid params - more checks later, depending on specific attack:
  if (!gamefield.validAttackInt(enemy_position) ||
      !gamefield.validGameFieldOrHand(attacker_position) ||
      preposition != Command::ATTACK_PREPOSITION)
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_WRONG_PARAMETER);
    return;
  }

  //Check for shields on enemy Field:
  has_shields = checkEnemyShield(enemy);

  //ATTACK PLAYER:
  attacker_position -= Command::VECTOR_OFFSET;
  if (enemy_position == Command::PLAYER_POSITON)
  {
    if (!validPlayerAttack(attacker_position, gamer))
    {
      io_over_cmd_.out(Interface::INFO,
          Interface::WARNING_EXECUTION_NOT_POSSIBLE);
      return;
    }
    if (!has_shields)
    {
      attackPlayer(gamefield, attacker_position, gamer, enemy_gamer);
      return;
    }
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_SHIELD_MONSTER);
    return;
  }
  enemy_position -= Command::VECTOR_OFFSET;

  //ATTACK CREATURES:
  if (!validCreatureAttack(attacker_position, enemy_position, gamer,
      enemy_gamer))
  {
    io_over_cmd_.out(Interface::INFO,
        Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }
  if (enemy[enemy_position]->getShield())
    shield_position = enemy_position;

  if ((has_shields && enemy_position == shield_position) || !has_shields)
    attackCreature(enemy_position, attacker_position, gamer, enemy_gamer);

  else
  {
    io_over_cmd_.out(Interface::INFO, Interface::WARNING_SHIELD_MONSTER);
    return;
  }
}

//------------------------------------------------------------------------------
void Attack::attackCreature(unsigned int opponent_position,
                            unsigned int friendly_position, Player *gamer,
                            Player *enemy_gamer)
{
  const CreatureCard *const *my_position = gamer->getGameField();

  //Attack enemy creature:
  int damage = my_position[friendly_position]->getDamagePoints();
  enemy_gamer->gotAttacked(opponent_position, damage);
  gamer->setAttacked(friendly_position);
}

//------------------------------------------------------------------------------
void Attack::attackPlayer(Oop::Game &gamefield,
                          unsigned int friendly_position, Player *gamer,
                          Player *enemy_gamer)
{
  const CreatureCard *const *my_position = gamer->getGameField();

  if (my_position[friendly_position] != nullptr &&
      my_position[friendly_position]->getType() ==
      Card::CardType::CREATURE &&
      !my_position[friendly_position]->getAlreadyAttacked() &&
      my_position[friendly_position]->getReadyToFight())
  {
    int enemy_mana = enemy_gamer->getManaPoints();
    bool mana_drain = my_position[friendly_position]->getManaDrain();
    int damage_to_player = my_position[friendly_position]->getDamagePoints();
    enemy_gamer->attackOnPlayer(damage_to_player);
    gamer->setAttacked(friendly_position);

    if (mana_drain)
    {
      enemy_gamer->reduceMana(enemy_mana);
    }
    if (enemy_gamer->isDead())
    {
      gamefield.killedEnemy(true);
    }
    return;
  }
  else
  {
    io_over_cmd_.out(Interface::INFO,
                     Interface::WARNING_EXECUTION_NOT_POSSIBLE);
    return;
  }
}

//------------------------------------------------------------------------------
bool Attack::validCreatureAttack(unsigned int friendly_position,
                                 unsigned int opponent_position, Player *gamer,
                                 Player *enemy_gamer)
{
  const CreatureCard *const *my_position = gamer->getGameField();
  const CreatureCard *const *enemy = enemy_gamer->getGameField();

  if (my_position[friendly_position] == nullptr ||
      enemy[opponent_position] == nullptr)
  {
    return false;
  }
  bool can_be_attacked = enemy[opponent_position]->getReadyToFight();
  bool can_attack = !my_position[friendly_position]->getAlreadyAttacked() &&
                    my_position[friendly_position]->getReadyToFight();

  //Check if command can be executed:
  return (my_position[friendly_position]->getType() ==
  Card::CardType::CREATURE && can_attack && can_be_attacked);
}

//------------------------------------------------------------------------------
bool Attack::validPlayerAttack(unsigned int friendly_position, Player *gamer)
{
  const CreatureCard *const *my_position;
  my_position = gamer->getGameField();

  return my_position[friendly_position] != nullptr &&
         my_position[friendly_position]->getType() ==
         Card::CardType::CREATURE &&
         !my_position[friendly_position]->getAlreadyAttacked() &&
         my_position[friendly_position]->getReadyToFight();
}

//------------------------------------------------------------------------------
bool Attack::checkEnemyShield(const CreatureCard *const *enemy)
{
  unsigned int field_index;

  for (field_index = 0; field_index < static_cast<unsigned int>
  (Interface::NUM_OF_GAMEFIELD_CARDS); field_index++)
  {
    if (enemy[field_index] != nullptr && enemy[field_index]->getShield())
      return true;
  }
  return false;
}
