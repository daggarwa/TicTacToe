#pragma once
#include <string>

#include "core/BoardSquare.h"
/**
 * The Class Move.
 * Defines a move by a player on game board.
 *
 *  @author d
 */
class Move {
 public:
  /** The dest. */
  BoardSquare dest;

  /**
   * Instantiates a new move.
   */
  Move() : dest(BoardSquare(-1, -1)) {}

  /**
   * Instantiates a new move with given coordinates and moveType.
   *
   * @param c1 the c 1
   */
  Move(BoardSquare c1) : dest(c1) {}

  /**
   * Instantiates a new move from an existing move.
   *
   * @param other the other
   */
  Move(Move const& other) : dest(other.dest) {}

  std::string toString() const {
    return std::to_string(dest.r + 1) + std::string(1, (char)(dest.c + 65));
  }

  bool operator<(const Move& rhs) const {
    return this->toString() < rhs.toString();
  }
};
