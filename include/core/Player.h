#pragma once

#include "core/BoardSquareState.h"
/**
 * Defines a player
 *
 * @author d
 */
class Player {
  BoardSquareState m_playerSymbol;

 public:
  static const Player CROSS;
  static const Player NOUGHT;

  /**
   * Instantiates a new player with a symbol : O or X.
   *
   * @param playerSymbol
   */
  Player(BoardSquareState const& playerSymbol);

  /**
   * Returns the opponent of the current player
   *
   * @return opponent
   */
  Player opponent() const;

  bool operator==(const Player& rhs) const;

  /**
   * Returns color of current player
   *
   * @return playerSymbol
   */
  BoardSquareState playerSymbol() const;

  std::string toString() const;

  friend std::ostream& operator<<(std::ostream& Str, Player const& v);
};
