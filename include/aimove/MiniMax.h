#pragma once

#include <limits>
#include <vector>

#include "aimove/EvaluationFunction.h"
#include "aimove/SearchResult.h"
#include "aimove/SimpleSearcher.h"

#include "core/BoardSquareState.h"
#include "core/GameBoard.h"
#include "core/Move.h"
#include "core/Player.h"
/**
 * Class containing implementations for search methods evaluating AI players
 * next possible moves and returning best one using minimax
 *
 * @author d
 */
class MiniMax : public SimpleSearcher {
 public:
  static int signum(int x);

  virtual SearchResult simpleSearch(GameBoard const& board,
                                    Player const* player, const int depth,
                                    EvaluationFunction const& evfunction);

  /**
   * Checks if game is in end state
   *
   * @param gameBoard
   * @return true, if is in end state
   */
  bool isEndState(GameBoard const& board);
};