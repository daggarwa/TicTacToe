#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include "controller/GameController.h"
#include "core/AIPlayer.h"
#include "core/BoardSquareState.h"
#include "core/Move.h"
#include "core/RandomHumanPlayer.h"

std::unique_ptr<Player> Player::CROSS = std::make_unique<RandomHumanPlayer>(
    RandomHumanPlayer(BoardSquareState::CROSS));
std::unique_ptr<Player> Player::NOUGHT =
    std::make_unique<AIPlayer>(AIPlayer(BoardSquareState::NOUGHT));
auto X = BoardSquareState::CROSS;
auto O = BoardSquareState::NOUGHT;
auto _ = BoardSquareState::EMPTY;

const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                 GameConstants::SIZE>
    win_board1{{{_, X, _}, {_, O, _}, {_, X, _}}};

const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                 GameConstants::SIZE>
    win_board2{{{O, X, _}, {_, _, _}, {_, X, _}}};

const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                 GameConstants::SIZE>
    win_board3{{{O, X, X}, {_, _, _}, {_, _, _}}};

const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                 GameConstants::SIZE>
    draw_board4{{{X, _, _}, {_, _, _}, {_, _, _}}};

class GameTest {
  GameController controller;
  bool printDebugInfo;

 public:
  GameTest(bool _printDebugInfo)
      : controller(GameController()), printDebugInfo(_printDebugInfo) {}

  void play(std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                       GameConstants::SIZE> const& board,
            bool& isDraw, Player const*& winner) {
    Move move;
    GameBoard gameBoard;
    gameBoard.setGameBoard(board);
    controller.setGameBoard(gameBoard);
    Player::NOUGHT->setDifficulty(DifficultyLevel::MAX);
    controller.setPlayer(Player::NOUGHT.get());

    // Play till end of game
    while (!controller.endOfGame()) {
      if (printDebugInfo) {
        std::cout << playerString(controller.currentPlayer()) + "'s turn"
                  << std::endl;
      }
      move = controller.nextMove();
      controller.makeMove(move);
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
  std::string playerString(Player const* player) const {
    return player->playerSymbol() == BoardSquareState::CROSS ? "CROSS"
                                                             : "NOUGHT";
  }
};

int main(int argc, char** argv) {
  try {
    GameTest game(false);

    const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                     GameConstants::SIZE>
        win_boards[] = {win_board1, win_board2, win_board3};
    int test = 0;
    for (const auto& board : win_boards) {
      for (size_t i = 0; i < 100; i++) {
        bool isDraw = true;
        Player const* winner = Player::CROSS.get();
        game.play(board, isDraw, winner);
        assert(isDraw == false);
        assert(winner == Player::NOUGHT.get());
        std::cout << "Passed win test " << ++test << "/300" << std::endl;
      }
    }

    const std::array<std::array<BoardSquareState, GameConstants::SIZE>,
                     GameConstants::SIZE>
        draw_boards[] = {draw_board4};
    for (const auto& board : draw_boards) {
      for (size_t i = 0; i < 10; i++) {
        bool isDraw = true;
        Player const* winner = Player::CROSS.get();
        game.play(board, isDraw, winner);
        assert(isDraw == true || winner == Player::NOUGHT.get());
        std::cout << "Passed draw test " << i << "/10" << std::endl;
      }
    }
  } catch (...) {
    std::cout << "Exiting" << std::endl;
  }

  return 0;
}
