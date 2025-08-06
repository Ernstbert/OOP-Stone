//------------------------------------------------------------------------------
// JsonParser.hpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/schema.h"
#include "CreatureCard.hpp"
#include "SpellCard.hpp"

#include <algorithm>
#include <fstream>

namespace Oop
{
  class Card;

  class JsonParser
  {
    public:

      //------------------------------------------------------------------------
      // Constructor
      //
      JsonParser();

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      JsonParser(const JsonParser &original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      JsonParser &operator = (const JsonParser &original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~JsonParser() noexcept;

      //------------------------------------------------------------------------
      // The parseConfig method
      //
      bool parseConfig(rapidjson::Document &file_to_parse);

      //------------------------------------------------------------------------
      // The createCards method
      //
      bool createCards(rapidjson::Document &file_to_parse,
                       std::vector<Card *> *card_stack_);

      //------------------------------------------------------------------------
      // val_duplicates:
      // Takes a vector of card pointers and checks if the creatures
      // with identical names also have identical attributes
      // @param std::vector<Card*> sortme The vector of cards to be checked
      // @return bool True if duplicates are valid, else false
      //
      bool val_duplicates(std::vector<Card *> sort_me);
  };
}

#endif //JSONPARSER_HPP
