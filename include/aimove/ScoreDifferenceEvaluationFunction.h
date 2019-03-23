#pragma once

#include "aimove/EvaluationFunction.h"

#include "core/GameBoard.h"
#include "core/Player.h"
/**
 * Class implementing one evaluation function based on
 * difference in scores of both players at one stage of the game.
 *
 * @author d
 */
class ScoreDifferenceEvaluationFunction : public EvaluationFunction {
  int calculateScore(GameBoard const& board, Player const* player) const;

 public:
  virtual int evaluate(GameBoard const& board, Player const* player) const;
};
