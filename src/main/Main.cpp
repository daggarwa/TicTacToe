#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "aimove/DifficultyLevel.h"

#include "controller/GameController.h"

#include "core/AIPlayer.h"
#include "core/BoardSquareState.h"
#include "core/GameBoard.h"
#include "core/GameConstants.h"
#include "core/HumanPlayer.h"
#include "core/Move.h"

std::unique_ptr<Player> Player::CROSS =
    std::make_unique<HumanPlayer>(HumanPlayer(BoardSquareState::CROSS));
std::unique_ptr<Player> Player::NOUGHT =
    std::make_unique<AIPlayer>(AIPlayer(BoardSquareState::NOUGHT));

class GameMain {
 public:
  /** Instance for the game controller. */
  GameController controller;
  Player* player1;
  Player* player2;
  /**
  * Constructor
  */
  GameMain()
      : controller(GameController()),
        player1(Player::CROSS.get()),
        player2(Player::NOUGHT.get()) {}

  /**
  * Read the input choice by user.
  *
  * @return the choice input
  */
  int readInput() const {
    std::string input = "";
    int choice = 0;
    while (std::cin >> input) {
      try {
        choice = std::atoi(input.c_str());
      } catch (...) {
        std::cout << "Wrong choice. Try again: ";
        continue;
      }
      break;
    }

    return choice;
  }

  /**
  * Method to display various options to user for the game
  */
  void play() {
    std::cout << std::endl << "Let's begin!" << std::endl;
    std::cout << std::endl << "1. You vs Machine!" << std::endl;
    std::cout << std::endl << "2. You vs your Friend!" << std::endl;
    std::cout << std::endl << "3. Set Difficulty" << std::endl;
    std::cout << std::endl << "4. Choose Nought or Cross" << std::endl;
    std::cout << std::endl << "5. Exit" << std::endl;
    std::cout << std::endl << std::endl << "Select action: ";
    while (true) {
      switch (readInput()) {
        case 1:
          if (player2->playerSymbol() == BoardSquareState::CROSS) {
            if (Player::CROSS->type() != PlayerType::AI) {
              Player::CROSS =
                  std::make_unique<AIPlayer>(AIPlayer(BoardSquareState::CROSS));
            }
            player2 = Player::CROSS.get();
          } else if (player2->playerSymbol() == BoardSquareState::NOUGHT) {
            if (Player::NOUGHT->type() != PlayerType::AI) {
              Player::NOUGHT = std::make_unique<AIPlayer>(
                  AIPlayer(BoardSquareState::NOUGHT));
            }
            player2 = Player::NOUGHT.get();
          }
          startGame();
          break;
        case 2:
          if (player2->playerSymbol() == BoardSquareState::CROSS) {
            if (Player::CROSS->type() != PlayerType::HUMAN) {
              Player::CROSS = std::make_unique<HumanPlayer>(
                  HumanPlayer(BoardSquareState::CROSS));
            }
            player2 = Player::CROSS.get();
          } else if (player2->playerSymbol() == BoardSquareState::NOUGHT) {
            if (Player::NOUGHT->type() != PlayerType::HUMAN) {
              Player::NOUGHT = std::make_unique<HumanPlayer>(
                  HumanPlayer(BoardSquareState::NOUGHT));
            }
            player2 = Player::NOUGHT.get();
          }
          startGame();
          break;
        case 3:
          setDifficulty();
          break;
        case 4:
          chooseNoughtOrCross();
          break;
        case 5:
          exit(0);
        default:
          std::cout << "Wrong choice. Try again" << std::endl;
          break;
      }
    }
  }

  /**
  * Method is called when a new game is started
  */
  void startGame() {
    // If game is started fresh then reset everything.
    controller.setGameBoard(GameBoard());
    controller.setPlayer(player1);
    std::cout << controller.printGameBoard() << std::endl;
    // Play till end of game
    while (!controller.endOfGame()) {
      std::cout << playerString(controller.currentPlayer()) + "'s turn";
      std::cout << std::endl;

      auto move = controller.nextMove();
      std::cout << "Making move.." << std::endl;
      controller.makeMove(move);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << controller.printGameBoard();

      std::cout << std::endl << "Changing turn.." << std::endl;
      controller.changeTurn();
    }
    declareWinner();

    rematch();
  }

  /**
  * Method called to display next player's name.
  */
  std::string playerString(Player const* player) const {
    return player == Player::CROSS.get() ? "CROSS" : "NOUGHT";
  }
  /**
  * Method called when option is pressed to set the game difficulty.
  */
  void setDifficulty() {
    std::cout << std::endl
              << "1. EASY" << std::endl
              << "2. HARD" << std::endl
              << "3. MAX" << std::endl
              << std::endl
              << "Select difficulty: ";
    while (true) {
      switch (readInput()) {
        case 1:
          player2->setDifficulty(DifficultyLevel::EASY);
          play();
          break;
        case 2:
          player2->setDifficulty(DifficultyLevel::HARD);
          play();
          break;
        case 3:
          player2->setDifficulty(DifficultyLevel::MAX);
          play();
          break;
        default:
          std::cout << "Wrong choice. Try again: ";
      }
    }
  }

  /**
  * Method called when option is pressed to choose player symbol in main menu.
  *
  */
  void chooseNoughtOrCross() {
    std::cout << std::endl
              << "1. "
              << "CROSS" << std::endl
              << "2. "
              << "NOUGHT" << std::endl
              << std::endl
              << "Select cross or nought:";
    while (true) {
      switch (readInput()) {
        case 1:
          if (Player::CROSS->type() != PlayerType::HUMAN) {
            Player::CROSS = std::make_unique<HumanPlayer>(
                HumanPlayer(BoardSquareState::CROSS));
          }
          player1 = Player::CROSS.get();
          player2 = Player::NOUGHT.get();
          play();
          break;
        case 2:
          if (Player::NOUGHT->type() != PlayerType::HUMAN) {
            Player::NOUGHT =
                std::make_unique<HumanPlayer>((BoardSquareState::NOUGHT));
          }
          player1 = Player::NOUGHT.get();
          player2 = Player::CROSS.get();
          play();
          break;
        default:
          std::cout << "Wrong choice. Try again: ";
      }
    }
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
                << "Congratulations " << playerString(controller.getWinner())
                << std::endl;
      std::cout << controller.getWinner()->winMessage() << std::endl;
    }
  }

  /**
  * Method is called when current game ends and user can start another game.
  */
  void rematch() {
    std::cout << "Ready for another game? [y/n]";
    char input;
    while (true) {
      std::cin >> input;
      switch (input) {
        case 'y': {
          startGame();
          break;
        }
        case 'n': {
          std::cout << "Exiting game." << std::endl;
          exit(0);
        }
        default:
          std::cout << "Wrong choice. Try again: ";
      }
    }
  }

  /**
  * The main method.
  *
  * @param command line args
  */
};

int main(int argc, char** argv) {
  try {
    GameMain game;
    game.play();
  } catch (...) {
    std::cout << "Exiting" << std::endl;
  }

  return 0;
}
