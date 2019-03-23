#include "core/RandomHumanPlayer.h"

#include <algorithm>
#include <iostream>

#include "core/GameBoard.h"
#include "core/Move.h"

Move RandomHumanPlayer::nextMove(GameBoard const& board_) const {
  GameBoard board(board_);
  auto moves = this->markPossibleMoves(board);
  this->unmarkPossibleMoves(board);
  std::sort(moves.begin(), moves.end());
  int moveIdx = 0;
  moveIdx = rand() % moves.size();
  return moves[moveIdx];
};
