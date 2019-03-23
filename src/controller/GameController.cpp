#include "controller/GameController.h"

GameController::GameController()
    : gameBoard(), player(Player::CROSS), depth(DifficultyLevel::EASY) {}

void GameController::setPlayer(Player const& a_player) { player = a_player; }

GameBoard GameController::getGameBoard() const { return gameBoard; }

void GameController::setGameBoard(GameBoard const& a_gameBoard) {
  gameBoard = a_gameBoard;
}

std::vector<Move> GameController::markPossibleMoves() {
  std::vector<Move> moves = gameBoard.getPossibleMoves(player);
  gameBoard.markPossibleMoves(moves);
  return moves;
}

void GameController::unmarkPossibleMoves() { gameBoard.unmarkPossibleMoves(); }

void GameController::makeMove(Move squares) {
  gameBoard.makeMove(squares, player.playerSymbol());
}

Player GameController::getWinner() {
  return gameBoard.checkIfWon(Player::NOUGHT) ? Player::NOUGHT : Player::CROSS;
}

bool GameController::isDraw() {
  return !gameBoard.checkIfWon(Player::NOUGHT) &&
         !gameBoard.checkIfWon(Player::CROSS);
}

bool GameController::endOfGame() {
  return gameBoard.isBoardFilledCompletely() ||
         gameBoard.checkIfWon(Player::NOUGHT) ||
         gameBoard.checkIfWon(Player::CROSS);
}

void GameController::changeTurn() { player = player.opponent(); }

Player GameController::currentPlayer() const { return player; }

std::string GameController::printGameBoard() { return gameBoard.toString(); }

void GameController::setDifficulty(DifficultyLevel level) { depth = level; }

Move GameController::evaluateMove() {
  MiniMax searcher = MiniMax();
  return searcher
      .simpleSearch(gameBoard, player, static_cast<int>(depth),
                    ScoreDifferenceEvaluationFunction())
      .getMove();
}
