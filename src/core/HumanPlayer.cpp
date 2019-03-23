#include "core/HumanPlayer.h"

#include <algorithm>
#include <iostream>

#include "core/GameBoard.h"
#include "core/Move.h"

Move HumanPlayer::selectMove(std::vector<Move>& moves) const {
  std::sort(moves.begin(), moves.end());
  int moveIdx = 0;
  std::cout << std::endl;
  std::cout << "Possible moves:" << std::endl;
  for (int i = 0; i < moves.size(); i++) {
    std::printf("%d: ", ++moveIdx);
    std::printf("%d%c\t", moves[i].dest.r + 1, moves[i].dest.c + 65);
  }
  std::cout << std::endl;
  std::cout << std::endl << "Select move: ";

  std::cin >> moveIdx;

  while (moveIdx <= 0 || moveIdx > moves.size()) {
    std::cout << "Wrong choice. Try again: ";
    std::cin >> moveIdx;
  }
  return moves[moveIdx - 1];
}

std::vector<Move> HumanPlayer::markPossibleMoves(GameBoard& board) const {
  std::vector<Move> moves = board.getPossibleMoves();
  board.markPossibleMoves(moves);
  return moves;
}

void HumanPlayer::unmarkPossibleMoves(GameBoard& board) const {
  board.unmarkPossibleMoves();
}

Move HumanPlayer::nextMove(GameBoard const& board_) const {
  GameBoard board(board_);
  auto possibleMoves = this->markPossibleMoves(board);
  std::cout << board.toString();
  this->unmarkPossibleMoves(board);
  return selectMove(possibleMoves);
};
