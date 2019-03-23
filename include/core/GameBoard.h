#pragma once

#include <array>
#include <string>
#include <vector>

#include "core/BoardSquare.h"
#include "core/BoardSquareState.h"
#include "core/BoardStats.h"
#include "core/Move.h"
#include "core/Player.h"

/**
 * The Class GameBoard.
 * Contains methods that define and manipulate the game board.
 *
 * @author d
 */
class GameBoard {
  std::vector<std::vector<BoardSquareState>> gameBoard;
  BoardStats stats;

  /**
   * Checks if any row on the board is filled up with some player's symbol
   *
   * @param input board square state
   * @param rowIndex
   * @return true or false
   */
  bool checkRowComplete(BoardSquareState const& state, size_t rowIndex) const;

  /**
   * Checks if any row or column on the board is filled up with some player's
   * symbol
   *
   * @param input board square state
   * @return true or false
   */
  bool checkAnyRowOrColumnComplete(BoardSquareState const& state) const;

  /**
   * Checks if any column on the board is filled up with some player's symbol
   *
   * @param input board square state
   * @param colIndex
   * @return true or false
   */
  bool checkColumnComplete(BoardSquareState const& state,
                           size_t colIndex) const;
  /**
   * Checks if diagonal on the board is filled up with some player's symbol
   *
   * @param input board square state
   * @return true or false
   */
  bool checkDiagonalComplete(BoardSquareState const& state) const;
  /**
   * Checks if reverse diagnol on the board is filled up with some player's
   * symbol
   *
   * @param input board square state
   * @return true or false
   */
  bool checkRevDiagonalComplete(BoardSquareState const& state) const;

 public:
  // Instantiates a new game board.

  GameBoard();

  /**
   * Gets the game board.
   *
   * @return the game board
   */
  std::vector<std::vector<BoardSquareState>> const& getGameBoard() const;

  BoardStats getStats() const;

  /**
   * Sets the game board.
   *
   * @param gameBoard the new game board
   */
  void setGameBoard(
      std::vector<std::vector<BoardSquareState>> const& gameBoard);

  /**
   * Instantiates a new game board from an existing board.
   * Deep copy
   * @param board
   */
  GameBoard(GameBoard const& board);

  /**
   * Gets the square state.
   *
   * @param square the square
   * @return the state of input square
   */
  BoardSquareState getSquareState(BoardSquare const& square) const;

  /**
   * Reset game board.
   */
  void resetGameBoard();

  /**
   * Gets the squares.
   *
   * @param input board square state (cross ,nought, or empty)
   * @return std::vector of squares in the input state
   */
  std::vector<BoardSquare> getSquares(BoardSquareState const& state) const;

  /**
   * Checks if is board filled completely.
   *
   * @return true, if board is filled completely
   */
  bool isBoardFilledCompletely() const;

  /**
   * Checks if player has won the game based on current board state
   *
   * @param player
   * @return true if won else false
   */
  bool checkIfWon(Player const& player) const;

  /**
   * Gets the possible moves.
   *
   * @param player
   * @return list of possible moves for the player
   */
  std::vector<Move> getPossibleMoves(Player const& player) const;

  /**
   * Marks possible moves on the board for the player to see.
   *
   * @param list of possibleMoves
   */
  void markPossibleMoves(std::vector<Move> const& possibleMoves);

  /**
   * Unmarks the possible moves on the board.
   */
  void unmarkPossibleMoves();

  /**
   * Make the move for the player on game board
   *
   * @param input move
   * @param final board state after move
   */
  void makeMove(Move const& squares, BoardSquareState const& state);

  std::string toString() const;
};
