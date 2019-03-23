#include "core/AIPlayer.h"

#include "aimove/MiniMax.h"
#include "aimove/ScoreDifferenceEvaluationFunction.h"

void AIPlayer::setDifficulty(DifficultyLevel level) { depth = level; }

Move AIPlayer::nextMove(GameBoard const& board) const {
  MiniMax searcher = MiniMax();
  return searcher.simpleSearch(board, this, static_cast<int>(depth),
                    ScoreDifferenceEvaluationFunction()).getMove();
}
