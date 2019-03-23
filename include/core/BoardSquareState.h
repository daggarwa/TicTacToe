#pragma once

#include <string>

#include "core/GameConstants.h"
/**
* Describes the state of a boardsquare on the game board
*
* @author d
*/
enum class BoardSquareState {

  CROSS = 0,
  NOUGHT = 1,
  EMPTY = 2,
  POTENTIALMOVE = 3

};

std::string stateToString(const BoardSquareState& state);