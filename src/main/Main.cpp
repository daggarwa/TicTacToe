#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "aimove/DifficultyLevel.h"

#include "controller/GameController.h"

#include "core/BoardSquareState.h"
#include "core/GameBoard.h"
#include "core/GameConstants.h"
#include "core/Move.h"
#include "core/Player.h"

const Player Player::CROSS(BoardSquareState::CROSS);
const Player Player::NOUGHT(BoardSquareState::NOUGHT);

class GameMain {
 public:
  /** Instance for the game controller. */
  GameController controller;

  /** Object to represent human player */
  Player human;

  /** Variable for tracking if opponent is AI player or not*/
  bool isOpponentAIPlayer = false;

  /**
  * Constructor
  */
  GameMain() : controller(GameController()), human(Player::CROSS) {}

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
          isOpponentAIPlayer = true;
          startGame();
          break;
        case 2:
          isOpponentAIPlayer = false;
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
    std::vector<Move> possibleMoves = std::vector<Move>();
    Move move;
    // If game is started fresh then reset everything.
    controller.getGameBoard().resetGameBoard();
    controller.setPlayer(human);
    std::cout << controller.printGameBoard() << std::endl;
    std::cout << playerString(human) + "'s turn";
    // Play till end of game
    while (!controller.endOfGame()) {
      possibleMoves.clear();
      if (controller.currentPlayer() == human || !isOpponentAIPlayer) {
        possibleMoves = controller.markPossibleMoves();
        std::cout << controller.printGameBoard();
        controller.unmarkPossibleMoves();
      }
      // Human player making move from possible moves
      if (!possibleMoves.empty()) {
        move = selectMove(possibleMoves);
        std::cout << "Making move.." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        controller.makeMove(move);
        std::cout << controller.printGameBoard();

      }  // AI player making move from possible moves
      else if (isOpponentAIPlayer &&
               controller.currentPlayer() == human.opponent()) {
        move = controller.evaluateMove();
        std::cout << std::endl << "Making move..";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        controller.makeMove(move);
        std::cout << controller.printGameBoard();
      }  // Timed out and failed to make move
      else {
        std::cout << std::endl
                  << "Oh! " << controller.currentPlayer() << " lost his turn"
                  << std::endl;
      }

      std::cout << std::endl << "Changing turn.." << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      controller.changeTurn();

      std::cout << std::endl;
      std::cout << playerString(controller.currentPlayer()) + "'s turn"
                << std::endl;
    }
    declareWinner();

    rematch();
  }

  /**
  * Select move from given possible moves on screen.
  *
  * @param list of possible moves
  * @return selected move
  */
  Move selectMove(std::vector<Move>& moves) const {
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
    moveIdx = readInput();
    while (moveIdx <= 0 || moveIdx > moves.size()) {
      std::cout << "Wrong choice. Try again: ";
      moveIdx = readInput();
    }
    return moves[moveIdx - 1];
  }

  /**
  * Method called to display next player's name.
  */
  std::string playerString(const Player& player) const {
    return player == BoardSquareState::CROSS ? "CROSS" : "NOUGHT";
  }
  /**
  * Method called when option is pressed to set the game difficulty.
  */
  void setDifficulty() {
    std::cout << std::endl
              << "1. EASY" << std::endl
              << "2. NORMAL" << std::endl
              << "3. HARD" << std::endl
              << "4. HEROIC" << std::endl
              << std::endl
              << "Select difficulty: ";
    while (true) {
      switch (readInput()) {
        case 1:
          controller.setDifficulty(DifficultyLevel::EASY);
          play();
          break;
        case 2:
          controller.setDifficulty(DifficultyLevel::NORMAL);
          play();
          break;
        case 3:
          controller.setDifficulty(DifficultyLevel::HARD);
          play();
          break;
        case 4:
          controller.setDifficulty(DifficultyLevel::HEROIC);
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
              << "1. " << Player::CROSS << std::endl
              << "2. " << Player::NOUGHT << std::endl
              << std::endl
              << "Select cross or nought:";
    while (true) {
      switch (readInput()) {
        case 1:
          human = Player::CROSS;
          play();
          break;
        case 2:
          human = Player::NOUGHT;
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
                << "Congratulations " << controller.getWinner() << std::endl;
      if (isOpponentAIPlayer &&
          controller.getWinner().playerSymbol() ==
              human.opponent().playerSymbol()) {
        std::cout << std::endl << "==> Robots rule us!!" << std::endl;
      }
    }
  }

  /**
  * Method is called when current game ends and user can start another game.
  */
  void rematch() {
    std::cout << "Ready for another game? [y/n]";
    char input;
    std::cin >> input;
    while (true) {
      switch (input) {
        case 'y': {
          controller = GameController();
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
