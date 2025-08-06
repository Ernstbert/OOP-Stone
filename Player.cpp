//------------------------------------------------------------------------------
// Player.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Player.hpp"

using Oop::Player;

//------------------------------------------------------------------------------
Player::Player() : name_(""), life_points_(30), mana_points_(0)
{
  is_dead_ = false;
}

//------------------------------------------------------------------------------
Player::Player(std::string name)
    : name_(name), life_points_(30), mana_points_(0)
{
}

//------------------------------------------------------------------------------
Player &Player::operator= (const Player &original)
{
  return *this;
}

//------------------------------------------------------------------------------
Player::~Player() noexcept
{
}

//------------------------------------------------------------------------------
void Player::setName(std::string player_name_)
{
  name_ = player_name_;
}

//------------------------------------------------------------------------------
void Player::addLifePoints(int points)
{
  life_points_ += points;
}

//------------------------------------------------------------------------------
void Player::addMana(int mana)
{
  //Managain doubles up to a max of +8 mana:
  if (mana >= 3)
  {
    mana_points_ += Interface::MAX_MANA_GAIN;
    if (mana_points_ > Interface::MAX_MANA)
    {
      mana_points_ = Interface::MAX_MANA;
      return;
    }
    return;
  }
  //In first round
  if (mana == 0)
  {
    mana_points_ = Card::START_MANA;
    return;
  }
  mana_points_ += (Card::MANA_GAIN_FACTOR * mana);
}

//------------------------------------------------------------------------------
void Player::reduceMana(int mana)
{
  mana_points_ -= mana;
  if (mana_points_ < 0)
  {
    mana_points_ = 0;
  }
}

//------------------------------------------------------------------------------
std::vector<Oop::Card *> Player::getHandCards() const
{
  return hand_;
}

//------------------------------------------------------------------------------
int Player::getHandSize() const
{
  return hand_.size();
}

//------------------------------------------------------------------------------
const Oop::CreatureCard *const *Player::getGameField() const
{
  return game_field_;
}

//------------------------------------------------------------------------------
void Player::setPickUpStack(const std::vector<Card *> &card_stack)
{
  for (auto shuffled_card : card_stack)
  {
    if (shuffled_card != nullptr)
    {
      pick_up_stack_.push_back(shuffled_card);
    }
  }
}

//------------------------------------------------------------------------------
void Player::setHand()
{
  for (int start_cards = 0; start_cards < Card::START_CARDS_AMAOUNT;
  start_cards++)
  {
    if (!pick_up_stack_.empty())
    {
      hand_.push_back(pick_up_stack_.back());
      pick_up_stack_.pop_back();
    }
  }
}

//------------------------------------------------------------------------------
bool Player::pickUpCard()
{
  if (getHandSize() < Interface::NUM_OF_GAMEFIELD_CARDS)
  {
    if (!pick_up_stack_.empty())
    {
      hand_.push_back(pick_up_stack_.back());
      pick_up_stack_.pop_back();
      return true;
    }
    else
    {
      //Card stack is empty:
      return reduceLifePoints(Card::PICK_UP_FAIL_LIFE_LOSS);
    }
  }
  else
  {
    //Hand is full:
    return reduceLifePoints(Card::PICK_UP_FAIL_LIFE_LOSS);
  }
}

//------------------------------------------------------------------------------
void Player::setCard(unsigned int hand_position, unsigned int field_position)
{
  if (hand_[hand_position] != nullptr && game_field_[field_position] == nullptr)
  {
    std::vector<CreatureCard *> creatures_;
    creatures_.push_back(dynamic_cast<CreatureCard *>(hand_[hand_position]));

    game_field_[field_position] = creatures_.back();
    hand_.erase(hand_.begin() + hand_position);
    creatures_.pop_back();
  }
}

//------------------------------------------------------------------------------
void Player::wakeUp()
{
  for (auto &field_itr : game_field_)
  {
    if (field_itr != nullptr)
    {
      //Set ready_to_fight_ true after 1 round:
      if (field_itr->getSleepyCounter() == Card::SLEEP_ROUNDS &&
      !field_itr->getReadyToFight())
      {
        field_itr->setReadyToFight(true);
      }
      if (!field_itr->getReadyToFight())
      {
        field_itr->sleepyCount();
      }
    }
  }
}

//------------------------------------------------------------------------------
bool Player::checkMana(unsigned int hand_position)
{
  // Check Manacost:
  int mana_to_remove = hand_[hand_position]->getManaCost();
  if (mana_to_remove > mana_points_)
  {
    return false;
  }
  else
  {
    reduceMana(mana_to_remove);
    return true;
  }
}

//------------------------------------------------------------------------------
bool Player::reduceLifePoints(int points)
{
  life_points_ -= points;
  return life_points_ >= Card::MIN_PLAYER_LIFE;
}

//------------------------------------------------------------------------------
void Player::setAttacked(unsigned int position)
{
  game_field_[position]->setAlreadyAttacked(true);
}

//------------------------------------------------------------------------------
void Player::gotAttacked(unsigned int attacked_position, int damage)
{
  int life_before = game_field_[attacked_position]->getCurrentLifePoints();
  int life_after = life_before - damage;
  if (life_after <= 0)
  {
    std::vector<CreatureCard *> dead_creature;
    dead_creature.push_back(game_field_[attacked_position]);
    graveyard_.push_back(dead_creature.back());
    dead_creature.pop_back();
    game_field_[attacked_position] = nullptr;
    return;
  }
  if (game_field_[attacked_position] != nullptr)
  {
    game_field_[attacked_position]->setCurrentLifePoints(life_after);
  }
}

//------------------------------------------------------------------------------
void Player::canAttackAgain()
{

  for (auto &index : game_field_)
  {
    if (index != nullptr)
    {
      if (index->getAttackAgain() == Card::SLEEP_ROUNDS &&
      index->getAlreadyAttacked())
      {
        index->setAlreadyAttacked(false);
      }
      if (index->getAlreadyAttacked())
      {
        index->attackAgainCount();
      }
    }
  }
}

//------------------------------------------------------------------------------
void Player::attackOnPlayer(int damage)
{

  if (!reduceLifePoints(damage))
  {
    setDead(true);
  }
}

//------------------------------------------------------------------------------
void Player::setDead(bool dead)
{
  is_dead_ = dead;
}

//------------------------------------------------------------------------------
bool Player::isDead() const
{
  return is_dead_;
}

//------------------------------------------------------------------------------
void Player::wakeUpShield()
{
  for (auto &index : game_field_)
  {
    if (index != nullptr)
    {
      if (index->getShield())
      {
        index->setReadyToFight(true);
      }
    }
  }
}

//------------------------------------------------------------------------------
std::vector<Oop::CreatureCard *> Player::getGraveyard() const
{
  return graveyard_;
}

//------------------------------------------------------------------------------
void Player::sacrificeCard(unsigned int hand_position, Card::CardType type)
{
  //Sacrifice spell -> spell destroyed
  if (type == Card::SPELL)
  {
    hand_.erase(hand_.begin() + hand_position);
  }
  //Sacrifice creature -> creature on graveyard
  else if (type == Card::CREATURE)
  {
    std::vector<CreatureCard *> sacrificed;
    sacrificed.push_back(dynamic_cast<CreatureCard *>(hand_[hand_position]));
    graveyard_.push_back(sacrificed.back());
    sacrificed.pop_back();
    hand_.erase(hand_.begin() + hand_position);
  }
}

//------------------------------------------------------------------------------
std::string Player::getName() const
{
  return name_;
}

//------------------------------------------------------------------------------
int Player::getLifePoints() const
{
  return life_points_;
}

//------------------------------------------------------------------------------
int Player::getManaPoints() const
{
  return mana_points_;
}

//------------------------------------------------------------------------------
Oop::SpellCard::SpellType Player::getSpell(unsigned int spell_position)
{
  std::vector<SpellCard *> spells;
  SpellCard::SpellType some_type;

  //Get spelltype and destroy card:
  spells.push_back(dynamic_cast<SpellCard *>(hand_[spell_position]));
  some_type = spells.back()->getSpellType();

  //Clean up cards:
  spells.pop_back();
  hand_.erase(hand_.begin() + spell_position);

  return some_type;
}

//------------------------------------------------------------------------------
void Player::healCreatures()
{
  for (auto &index : game_field_)
  {
    if (index != nullptr)
    {
      int life_before = index->getCurrentLifePoints();
      int life_after = life_before + Card::CREATURE_HEAL;
      if (life_after <= Card::CREATURE_MAX_LIFE)
      {
        index->setCurrentLifePoints(life_after);
      }
    }
  }
}

//------------------------------------------------------------------------------
void Player::reliefYourself()
{
  for (int repeat = 0; repeat < 3; repeat++)
  {
    if (!pickUpCard())
    {
      setDead(true);
    }
  }
}

//------------------------------------------------------------------------------
void Player::respawnCreature()
{
  int base_life = graveyard_.back()->getLifePoints();
  graveyard_.back()->setCurrentLifePoints(base_life);
  graveyard_.back()->setReadyToFight(false);
  graveyard_.back()->setAlreadyAttacked(false);

  for (auto &index : game_field_)
  {
    if (index == nullptr)
    {
      index = graveyard_.back();
      break;
    }
  }
  graveyard_.pop_back();
}
