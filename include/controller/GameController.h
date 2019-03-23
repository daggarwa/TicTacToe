#pragma once

#include <string>
#include <vector>

#include "aimove/DifficultyLevel.h"
#include "aimove/EvaluationFunction.h"
#include "aimove/MiniMax.h"
#include "aimove/ScoreDifferenceEvaluationFunction.h"

#include "core/BoardSquareState.h"
#include "core/GameBoard.h"
#include "core/GameConstants.h"
#include "core/Move.h"
#include "core/Player.h"

/**
 * Class is controller for the game.
 *
 * @author d
 */
class GameController {
  GameBoard gameBoard;

  Player const* player;

 public:
  /**
   * Instantiates a new game controller.
   */
  GameController();

  /**
   * Sets the player.
   *
   * @param player
   */
  void setPlayer(Player const* a_player);

  /**
   * Gets the game board.
   *
   * @return the game board
   */
  GameBoard getGameBoard() const;

  /**
   * Sets the game board.
   *
   * @param gameBoard the new game board
   */
  void setGameBoard(GameBoard const& a_gameBoard);

  /**
   * Calls the gameboard method to make the next
   * move on the game board
   *
   * @param move to make
   */
  void makeMove(Move squares);

  /**
   * Calculates winner of the game based on score.
   *
   * @return the winner
   */
  Player const* getWinner();

  /**
   * Checks if game ends in a draw.
   *
   * @return true, if game is drawn
   */
  bool isDraw();

  /**
   * Check if game has ended.
   *
   * @return true, if successful
   */
  bool endOfGame();

  /**
   * Changes turn to allow next player to play.
   */
  void changeTurn();

  /**
   * Returns the current player
   *
   * @return the player
   */
  Player const* currentPlayer() const;

  /**
   * Prints the game board.
   *
   * @return the string
   */
  std::string printGameBoard();

  Move nextMove() const;
};
