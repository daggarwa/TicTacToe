#pragma once

#include "Player.h"

class AIPlayer : public Player {
  /** Variable that is set to the number of moves ahead AIPlayer evaluates
  * to select from current possible moves */
  DifficultyLevel depth;
  /**
  * Sets the difficulty level.
  *
  * @param difficulty level
  */
 public:
  virtual void setDifficulty(DifficultyLevel level) override;
  AIPlayer(BoardSquareState const& playerSymbol)
      : Player(playerSymbol, PlayerType::AI), depth(DifficultyLevel::EASY) {}
  virtual Move nextMove(GameBoard const& board) const;
  virtual std::string winMessage() const { return "==> Robots rule us!!"; }
};
