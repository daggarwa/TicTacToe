#pragma once
/**
* The Class BoardStats.
* Maintains counts for board square states
* as per each player's move on the game board.
*
* @author d
*/
class BoardStats {
 public:
  std::array<std::array<size_t, 3>, GameConstants::SIZE> rowCounts;
  std::array<std::array<size_t, 3>, GameConstants::SIZE> colCounts;
  std::array<size_t, 3> diagCounts;
  std::array<size_t, 3> revDiagCounts;

  BoardStats()
      : rowCounts({0}), colCounts({0}), diagCounts({0}), revDiagCounts({0}) {}
};