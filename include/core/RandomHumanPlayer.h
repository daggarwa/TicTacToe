#pragma once

#include "HumanPlayer.h"

class RandomHumanPlayer : public HumanPlayer {
 public:
  RandomHumanPlayer(BoardSquareState const& playerSymbol)
      : HumanPlayer(playerSymbol) {}
  virtual Move nextMove(GameBoard const& board) const;
};
