#pragma once
#include <memory>

#include "aimove/DifficultyLevel.h"
#include "core/BoardSquareState.h"

class Move;
class GameBoard;

/**
 * Defines a player
 *
 * @author d
 */
enum class PlayerType { HUMAN = 0, AI = 1 };

class Player {
  BoardSquareState m_playerSymbol;
  PlayerType m_type;

 public:
  static std::unique_ptr<Player> CROSS;
  static std::unique_ptr<Player> NOUGHT;

  /**
   * Instantiates a new player with a symbol : O or X.
   *
   * @param playerSymbol
   */
  Player(BoardSquareState const& playerSymbol, PlayerType type);

  /**
   * Returns the opponent of the current player
   *
   * @return opponent
   */
  Player const* opponent() const;

  bool operator==(const Player& rhs) const;

  PlayerType type() const;
  /**
   * Returns symbol of current player
   *
   * @return playerSymbol
   */
  BoardSquareState playerSymbol() const;

  std::string toString() const;

  virtual void setDifficulty(DifficultyLevel level) {}

  virtual std::string winMessage() const { return ""; }
  virtual Move nextMove(GameBoard const& board) const = 0;

  friend std::ostream& operator<<(std::ostream& Str, Player const& v);
};
