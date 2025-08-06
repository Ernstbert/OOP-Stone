//------------------------------------------------------------------------------
// Command.cpp
//
// Group: Group 11.17, study assistant David Andrawes
//
// Authors: Damalas, Stelios-Andreas 09132052
// Horvath, Joachim Karl 01131128
// Straka, Anton  - N/A
//------------------------------------------------------------------------------
//

#include "Command.hpp"

using Oop::Command;

//------------------------------------------------------------------------------
// static constants used in commands:
const unsigned int Command::VECTOR_OFFSET = 1;
const unsigned int Command::PLAYER_POSITON = 0;
const unsigned int Command::EXECUTION_IMPOSSIBLE = 8;
const int Command::SACRIFICE_GAIN = 1;

const std::string Command::ATTACK_PREPOSITION = "with";
const std::string Command::SET_PREPOSITION = "to";

//------------------------------------------------------------------------------
Command::Command(Interface &io_over_cmd) : io_over_cmd_(io_over_cmd)
{
}

//------------------------------------------------------------------------------
Command::~Command() noexcept
{
}

