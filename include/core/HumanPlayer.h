#pragma once

#include<vector>

#include "Player.h"

class HumanPlayer : public Player {
 protected:
  std::vector<Move> markPossibleMoves(GameBoard& board) const;
  void unmarkPossibleMoves(GameBoard& board) const;
  /**
  * Select move from given possible moves on screen.
  *
  * @param list of possible moves
  * @return selected move
  */
  Move selectMove(std::vector<Move>& moves) const;

 public:
  HumanPlayer(BoardSquareState const& playerSymbol)
      : Player(playerSymbol, PlayerType::HUMAN) {}
  virtual Move nextMove(GameBoard const& board) const;
  virtual std::string winMessage() const { return "We have hope after all"; }
};
