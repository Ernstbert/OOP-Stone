//------------------------------------------------------------------------------
// JsonParser.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "JsonParser.hpp"

using Oop::JsonParser;

//------------------------------------------------------------------------------
JsonParser::JsonParser() = default;

//------------------------------------------------------------------------------
JsonParser::~JsonParser() noexcept
{
}

//------------------------------------------------------------------------------
bool JsonParser::parseConfig(rapidjson::Document &file_to_parse)
{
  if (file_to_parse.HasParseError())
    return false;

  //open and parse schema.json:
  std::ifstream schema_file_stream("schema.json");
  rapidjson::IStreamWrapper schema_stream(schema_file_stream);
  rapidjson::Document schema;
  schema.ParseStream(schema_stream);

  //checking for parse errors/valid json in schema:
  if (schema.HasParseError())
    return false;

  // Compile a Document to SchemaDocument and use it to validate input-json:
  rapidjson::SchemaDocument schema_document(schema);
  rapidjson::SchemaValidator validator(schema_document);
  return file_to_parse.Accept(validator);
}

//------------------------------------------------------------------------------
bool JsonParser::createCards(rapidjson::Document &file_to_parse,
                             std::vector<Card *> *card_stack_)
{
  //Creating CreatureCard objects and put in card_stack_:
  for (auto &creature_card : file_to_parse["Creatures"].GetArray())
  {
    if (creature_card.HasMember("speedy"))
    {
      card_stack_->push_back(new CreatureCard(creature_card["name"].GetString(),
                                        creature_card["mana_cost"].GetInt(),
                                        creature_card["damage_points"].GetInt(),
                                        creature_card["life_points"].GetInt(),
                                        creature_card["shield"].GetBool(),
                                        creature_card["mana_drain"].GetBool(),
                                        creature_card["speedy"].GetBool()));
    }
    else
    {
      card_stack_->push_back(new CreatureCard(creature_card["name"].GetString(),
                                creature_card["mana_cost"].GetInt(),
                                creature_card["damage_points"].GetInt(),
                                creature_card["life_points"].GetInt(),
                                creature_card["shield"].GetBool(),
                                creature_card["mana_drain"].GetBool(), false));
    }
  }
  //Creating SpellCard objects and put in card_stack_:
  for (auto &spell_card : file_to_parse["Spells"].GetArray())
  {
    std::string spell_name = spell_card["name"].GetString();
    if (spell_name == Interface::STRING_HEALER)
    {
      card_stack_->push_back(new SpellCard(SpellCard::HEALER));
    }
    else if (spell_name == Interface::STRING_RELIEF)
    {
      card_stack_->push_back(new SpellCard(SpellCard::RELIEF));
    }
    else if (spell_name == Interface::STRING_REBIRTH)
    {
      card_stack_->push_back(new SpellCard(SpellCard::REBIRTH));
    }
    else if (spell_name == Interface::STRING_DRACULA)
    {
      card_stack_->push_back(new SpellCard(SpellCard::DRACULA));
    }
    else
    {
      return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool JsonParser::val_duplicates(std::vector<Card *> sort_me)
{

  std::vector<CreatureCard *> creatures_;

  //sort the Card* vector by Card Name:
  std::sort(sort_me.begin(), sort_me.end(),
            [](const Card *cardname_lower, const Card *cardname_higher)
            {
              return cardname_lower->getName() < cardname_higher->getName();
            });

  //Fill CreatureCard* vector, because this only applies to creatures:
  for (auto &cards_iter : sort_me)
  {
    if (cards_iter->getType() == Card::CardType::CREATURE)
    {
      creatures_.push_back(dynamic_cast<CreatureCard *>(cards_iter));
    }
  }

  // Lambda func: compare duplicate names and attributes
  auto duplicates_ = [](const CreatureCard *lhs, const CreatureCard *rhs)
  {
    return (lhs->getName() == rhs->getName()) &&
           (lhs->getManaCost() != rhs->getManaCost() ||
            lhs->getDamagePoints() != rhs->getDamagePoints() ||
            lhs->getLifePoints() != rhs->getLifePoints() ||
            lhs->getShield() != rhs->getShield() ||
            lhs->getManaDrain() != rhs->getManaDrain() ||
            lhs->getSpeedy() != rhs->getSpeedy());
  };

  // Find out if duplicates are valid based on "duplicates_" conditions:
  const auto invalid_duplicate = std::adjacent_find(creatures_.begin(),
                                                    creatures_.end(),
                                                    duplicates_);
  return (invalid_duplicate == creatures_.end());
}



