#pragma once

#include <iostream>

#include <math.h>

/**
* The Class BoardSquare.
* Represents a square on the game board
*
* @author d
*/
class BoardSquare {
 public:
  int r;
  int c;
  /**
  * Instantiates a new board square.
  */
  BoardSquare() {
    r = 0;
    c = 0;
  }

  /**
  * Instantiates a new board square.
  * with input row and column coordinates
  *
  * @param r1 row coordinate
  * @param c1 column coordinate
  */
  BoardSquare(int r1, int c1) {
    r = r1;
    c = c1;
  }

  /**
  * Instantiates a new board square
  * from existing board square.
  *
  * @param square the square
  */
  BoardSquare(BoardSquare const& square) {
    r = square.r;
    c = square.c;
  }

  bool operator==(const BoardSquare& cother) const {
    if (r == cother.r && c == cother.c) return true;
    return false;
  }

  /**
  * Adds the coordinates of one board square to another.
  *
  * @param toAdd square to add
  * @return boardsquare object formed from added coordinates
  */
  BoardSquare add(BoardSquare const& toAdd) const {
    return BoardSquare(this->r + toAdd.r, this->c + toAdd.c);
  }

  friend std::ostream& operator<<(std::ostream& Str, BoardSquare const& v);
};
inline std::ostream& operator<<(std::ostream& Str, BoardSquare const& v) {
  Str << "(r=" << v.r << ",c=" << v.c << ")";
  return Str;
}