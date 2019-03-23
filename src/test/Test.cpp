#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "controller/GameController.h"

#include "core/BoardSquareState.h"
#include "core/Move.h"
#include "core/Player.h"

const Player Player::CROSS(BoardSquareState::CROSS);
const Player Player::NOUGHT(BoardSquareState::NOUGHT);
auto X = BoardSquareState::CROSS;
auto O = BoardSquareState::NOUGHT;
auto _ = BoardSquareState::EMPTY;

const std::vector<std::vector<BoardSquareState>> win_board1{
    {_, X, _}, {_, O, _}, {_, X, _}};

const std::vector<std::vector<BoardSquareState>> win_board2{
    {O, X, _}, {_, _, _}, {_, X, _}};

const std::vector<std::vector<BoardSquareState>> win_board3{
    {O, X, X}, {_, _, _}, {_, _, _}};

const std::vector<std::vector<BoardSquareState>> draw_board4{
    {X, _, _}, {_, _, _}, {_, _, _}};

class GameTest {
  GameController controller;
  Player human;
  bool printDebugInfo;

 public:
  GameTest(bool _printDebugInfo)
      : controller(GameController()),
        human(Player::CROSS),
        printDebugInfo(_printDebugInfo) {}

  void play(std::vector<std::vector<BoardSquareState>> const& board,
            bool& isDraw, Player& winner) {
    std::vector<Move> possibleMoves = std::vector<Move>();
    Move move;
    GameBoard gameBoard;
    gameBoard.setGameBoard(board);
    controller.setGameBoard(gameBoard);
    controller.setPlayer(human.opponent());
    controller.setDifficulty(DifficultyLevel::MAX);

    // Play till end of game
    while (!controller.endOfGame()) {
      if (printDebugInfo) {
        std::cout << playerString(controller.currentPlayer()) + "'s turn"
                  << std::endl;
      }
      possibleMoves.clear();
      if (controller.currentPlayer() == human) {
        possibleMoves = controller.markPossibleMoves();
        controller.unmarkPossibleMoves();
        move = selectRandomMove(possibleMoves);
        controller.makeMove(move);
      } else {
        move = controller.evaluateMove();
        controller.makeMove(move);
      }
      if (printDebugInfo) {
        std::cout << controller.printGameBoard();
        std::cout << std::endl;
      }
      controller.changeTurn();
    }
    if (printDebugInfo) {
      declareWinner();
    }
    isDraw = controller.isDraw();
    winner = controller.getWinner();
  }

  Move selectRandomMove(std::vector<Move>& moves) const {
    std::sort(moves.begin(), moves.end());
    int moveIdx = 0;
    moveIdx = rand() % moves.size();
    return moves[moveIdx];
  }

  /**
* Method displays the final winner when game has ended.
*/
  void declareWinner() {
    std::cout << controller.printGameBoard();
    if (controller.isDraw()) {
      std::cout << std::endl << ":: Game drawn!";
      std::cout << std::endl << "Joint party :)";
    } else {
      std::cout << std::endl << ":: We have a winner!";
      std::cout << std::endl
                << "Congratulations " << controller.getWinner() << std::endl;
    }
  }

  /**
  * Method called to display next player's name.
  */
  std::string playerString(const Player& player) const {
    return player == BoardSquareState::CROSS ? "CROSS" : "NOUGHT";
  }
};

int main(int argc, char** argv) {
  try {
    GameTest game(false);

    const std::vector<std::vector<BoardSquareState>> win_boards[] = {
        win_board1, win_board2, win_board3};
    int test = 0;
    for (const auto& board : win_boards) {
      for (size_t i = 0; i < 100; i++) {
        bool isDraw = true;
        Player winner(BoardSquareState::EMPTY);
        game.play(board, isDraw, winner);
        assert(isDraw == false);
        assert(winner == Player::NOUGHT);
        std::cout << "Passed win test " << ++test << "/300" << std::endl;
      }
    }

    const std::vector<std::vector<BoardSquareState>> draw_boards[] = {
        draw_board4};
    for (const auto& board : draw_boards) {
      for (size_t i = 0; i < 10; i++) {
        bool isDraw = true;
        Player winner(BoardSquareState::EMPTY);
        game.play(board, isDraw, winner);
        assert(isDraw == true || winner == Player::NOUGHT);
        std::cout << "Passed draw test " << i << "/10" << std::endl;
      }
    }
  } catch (...) {
    std::cout << "Exiting" << std::endl;
  }

  return 0;
}
