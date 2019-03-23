#include "controller/GameController.h"

GameController::GameController() : gameBoard(), player(Player::CROSS.get()) {}

void GameController::setPlayer(Player const* a_player) { player = a_player; }

GameBoard GameController::getGameBoard() const { return gameBoard; }

void GameController::setGameBoard(GameBoard const& a_gameBoard) {
  gameBoard = a_gameBoard;
}

void GameController::makeMove(Move squares) {
  gameBoard.makeMove(squares, player->playerSymbol());
}

Player const* GameController::getWinner() {
  return gameBoard.checkIfWon(Player::NOUGHT.get()) ? Player::NOUGHT.get()
                                                    : Player::CROSS.get();
}

bool GameController::isDraw() {
  return !gameBoard.checkIfWon(Player::NOUGHT.get()) &&
         !gameBoard.checkIfWon(Player::CROSS.get());
}

bool GameController::endOfGame() {
  return gameBoard.isBoardFilledCompletely() ||
         gameBoard.checkIfWon(Player::NOUGHT.get()) ||
         gameBoard.checkIfWon(Player::CROSS.get());
}

void GameController::changeTurn() { player = player->opponent(); }

Player const* GameController::currentPlayer() const { return player; }

std::string GameController::printGameBoard() { return gameBoard.toString(); }

Move GameController::nextMove() const { return player->nextMove(gameBoard); }
