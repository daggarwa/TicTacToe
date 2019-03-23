#include "aimove/MiniMax.h"

int MiniMax::signum(int x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

SearchResult MiniMax::simpleSearch(GameBoard const& board, Player const* player,
                                   const int depth,
                                   EvaluationFunction const& evfunction) {
  if (depth <= 0 || isEndState(board)) {
    return SearchResult(Move(), evfunction.evaluate(board, player));
  } else { /* there's more to check */
    std::vector<Move> possibleMoves = board.getPossibleMoves();

    SearchResult best =
        SearchResult(Move(), std::numeric_limits<int>::min() + 1);
    if (possibleMoves.empty()) { /* turn is lost - check next player */
      possibleMoves = board.getPossibleMoves();
      if (possibleMoves.empty()) { /* end of game - is there a winner ? */
        switch (MiniMax::signum(evfunction.evaluate(board, player))) {
          case -1:
            best = SearchResult(Move(), std::numeric_limits<int>::min() + 1);
            break;
          case 0:
            best = SearchResult(Move(), 0);
            break;
          case 1:
            best = SearchResult(Move(), std::numeric_limits<int>::max());
            break;
        }
      } else { /* game continues - no moves to check */
        best = simpleSearch(board, player->opponent(), depth - 1, evfunction)
                   .negated();
      }
    } else { /* check the score of each move */
      for (Move nextPossibleMove : possibleMoves) {
        GameBoard subBoard(board);
        subBoard.makeMove(nextPossibleMove, player->playerSymbol());
        int score =
            simpleSearch(subBoard, player->opponent(), depth - 1, evfunction)
                .negated()
                .getScore();
        if (best.getScore() < score) {
          /* store the best score and corresponding move */
          best = SearchResult(nextPossibleMove, score);
        }
      }
    }
    return best;
  }
}

bool MiniMax::isEndState(GameBoard const& board) {
  return board.isBoardFilledCompletely() ||
         board.checkIfWon(Player::CROSS.get()) ||
         board.checkIfWon(Player::NOUGHT.get());
}
