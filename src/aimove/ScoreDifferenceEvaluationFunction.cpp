#include "aimove/ScoreDifferenceEvaluationFunction.h"

#include <limits>
#include <cmath>

int ScoreDifferenceEvaluationFunction::calculateScore(
    GameBoard const& board, Player const& player) const {
  int score = 0;
  const auto& stats = board.getStats();
  auto p = static_cast<int>(player.playerSymbol());
  auto o = static_cast<int>(player.opponent().playerSymbol());
  for (size_t i = 0; i < GameConstants::SIZE; i++) {
    if (stats.rowCounts[i][o] == 0) {
      score += std::pow(10, stats.rowCounts[i][p]);
    }
    if (stats.colCounts[i][o] == 0) {
      score += std::pow(10, stats.colCounts[i][p]);
    }
  }
  if (stats.diagCounts[o] == 0) {
    score += std::pow(10, stats.diagCounts[p]);
  }
  if (stats.revDiagCounts[o] == 0) {
    score += std::pow(10, stats.revDiagCounts[p]);
  }
  return score;
}

int ScoreDifferenceEvaluationFunction::evaluate(GameBoard const& board,
                                                Player const& player) const {
  auto playerWon = board.checkIfWon(player);
  auto opponentWon = board.checkIfWon(player.opponent());

  if (playerWon) {
    return std::numeric_limits<int>::max();
  }
  if (opponentWon) {
    return std::numeric_limits<int>::min() + 1;
  }

  auto playerScore = calculateScore(board, player);
  auto opponentScore = calculateScore(board, player.opponent());
  return playerScore - opponentScore;
}
