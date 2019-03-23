#include "core/BoardSquareState.h"

std::string stateToString(const BoardSquareState& state) {
  char playerChar = ' ';
  switch (state) {
    case BoardSquareState::CROSS:
      playerChar = GameConstants::CROSS;
      break;
    case BoardSquareState::NOUGHT:
      playerChar = GameConstants::NOUGHT;
      break;
    case BoardSquareState::EMPTY:
      playerChar = GameConstants::EMPTY;
      break;
    case BoardSquareState::POTENTIALMOVE:
      playerChar = GameConstants::POTENTIALMOVE;
      break;
    default:
      break;
  }
  return std::string(1, playerChar);
}
