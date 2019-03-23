#include "core/GameBoard.h"

GameBoard::GameBoard() { this->resetGameBoard(); }

std::array<std::array<BoardSquareState, GameConstants::SIZE>,
           GameConstants::SIZE> const&
GameBoard::getGameBoard() const {
  return gameBoard;
}

BoardStats GameBoard::getStats() const { return this->stats; }

void GameBoard::setGameBoard(
    std::array<std::array<BoardSquareState, GameConstants::SIZE>,
               GameConstants::SIZE> const& gameBoard) {
  this->gameBoard = gameBoard;
  this->stats = BoardStats();
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      size_t s = static_cast<int>(gameBoard[i][j]);
      if (s < 3) {
        this->stats.rowCounts[i][s]++;
        this->stats.colCounts[j][s]++;
        if (i == j) {
          this->stats.diagCounts[s]++;
        }
        if (i == GameConstants::SIZE - j - 1) {
          this->stats.revDiagCounts[s]++;
        }
      }
    }
  }
}

GameBoard::GameBoard(GameBoard const& board) {
  this->resetGameBoard();
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      gameBoard[i][j] = board.gameBoard[i][j];
    }
    for (size_t s = 0; s < 3; s++) {
      stats.rowCounts[i][s] = board.stats.rowCounts[i][s];
      stats.colCounts[i][s] = board.stats.colCounts[i][s];
    }
  }
  for (size_t s = 0; s < 3; s++) {
    stats.diagCounts[s] = board.stats.diagCounts[s];
    stats.revDiagCounts[s] = board.stats.revDiagCounts[s];
  }
}

BoardSquareState GameBoard::getSquareState(BoardSquare const& square) const {
  return gameBoard[square.r][square.c];
}

void GameBoard::resetGameBoard() {
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      gameBoard[i][j] = BoardSquareState::EMPTY;
    }
    stats.rowCounts[i][2] = GameConstants::SIZE;
    stats.colCounts[i][2] = GameConstants::SIZE;
  }
  stats.diagCounts[2] = GameConstants::SIZE;
  stats.revDiagCounts[2] = GameConstants::SIZE;
}

std::vector<BoardSquare> GameBoard::getSquares(
    BoardSquareState const& state) const {
  std::vector<BoardSquare> listofSquaresInState = std::vector<BoardSquare>();
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      if (gameBoard[i][j] == state)
        listofSquaresInState.push_back(BoardSquare(i, j));
    }
  }
  return listofSquaresInState;
}

/**
* Checks if is board filled completely.
*
* @return true, if board is filled completely
*/
bool GameBoard::isBoardFilledCompletely() const {
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      if (gameBoard[i][j] == BoardSquareState::EMPTY) return false;
    }
  }
  return true;
}

bool GameBoard::checkRowComplete(BoardSquareState const& state,
                                 size_t rowIndex) const {
  if (rowIndex >= GameConstants::SIZE) {
    return false;
  }
  return (stats.rowCounts[rowIndex][static_cast<int>(state)] ==
          GameConstants::SIZE);
}

bool GameBoard::checkAnyRowOrColumnComplete(
    BoardSquareState const& state) const {
  for (size_t i = 0; i < GameConstants::SIZE; i++) {
    if (checkRowComplete(state, i)) {
      return true;
    }
    if (checkColumnComplete(state, i)) {
      return true;
    }
  }
  return false;
}

bool GameBoard::checkColumnComplete(BoardSquareState const& state,
                                    size_t colIndex) const {
  if (colIndex >= GameConstants::SIZE) {
    return false;
  }
  return (stats.colCounts[colIndex][static_cast<int>(state)] ==
          GameConstants::SIZE);
}

bool GameBoard::checkDiagonalComplete(BoardSquareState const& state) const {
  return (stats.diagCounts[static_cast<int>(state)] == GameConstants::SIZE);
}

bool GameBoard::checkRevDiagonalComplete(BoardSquareState const& state) const {
  return (stats.revDiagCounts[static_cast<int>(state)] == GameConstants::SIZE);
}

bool GameBoard::checkIfWon(Player const* player) const {
  if (checkAnyRowOrColumnComplete(player->playerSymbol()) ||
      checkDiagonalComplete(player->playerSymbol()) ||
      checkRevDiagonalComplete(player->playerSymbol())) {
    return true;
  }
  return false;
}

std::vector<Move> GameBoard::getPossibleMoves() const {
  std::vector<Move> possibleMoves = std::vector<Move>();
  std::vector<BoardSquare> currentSquareStateCellsList =
      std::vector<BoardSquare>();
  currentSquareStateCellsList = this->getSquares(BoardSquareState::EMPTY);
  for (auto& currentSquare : currentSquareStateCellsList) {
    possibleMoves.push_back(Move(currentSquare));
  }
  return possibleMoves;
}

void GameBoard::markPossibleMoves(std::vector<Move> const& possibleMoves) {
  for (size_t i = 0; i < possibleMoves.size(); i++) {
    BoardSquare point = possibleMoves[i].dest;
    gameBoard[point.r][point.c] = BoardSquareState::POTENTIALMOVE;
  }
}

void GameBoard::unmarkPossibleMoves() {
  for (int i = 0; i < GameConstants::SIZE; i++) {
    for (int j = 0; j < GameConstants::SIZE; j++) {
      if (gameBoard[i][j] == BoardSquareState::POTENTIALMOVE)
        gameBoard[i][j] = BoardSquareState::EMPTY;
    }
  }
}

void GameBoard::makeMove(Move const& squares, BoardSquareState const& state) {
  auto r = squares.dest.r;
  auto c = squares.dest.c;
  auto oldState = static_cast<int>(gameBoard[r][c]);
  gameBoard[r][c] = state;
  auto s = static_cast<int>(state);
  stats.rowCounts[r][s]++;
  stats.rowCounts[r][oldState]--;

  stats.colCounts[c][s]++;
  stats.colCounts[c][oldState]--;

  if (r == c) {
    stats.diagCounts[s]++;
    stats.diagCounts[oldState]--;
  }
  if (r == GameConstants::SIZE - c - 1) {
    stats.revDiagCounts[s]++;
    stats.revDiagCounts[oldState]--;
  }
}

std::string GameBoard::toString() const {
  BoardSquare point = BoardSquare();
  std::string sb;
  sb.append("\n  A B C ");
  for (point.r = 0; point.r < GameConstants::SIZE; point.r++) {
    sb.append("\n").append(std::to_string(point.r + 1));
    for (point.c = 0; point.c < GameConstants::SIZE; point.c++) {
      sb.append(" ").append(stateToString(gameBoard[point.r][point.c]));
    }
  }
  sb.append("\n");
  return sb;
}
