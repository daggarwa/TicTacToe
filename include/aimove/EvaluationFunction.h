#pragma once

class GameBoard;
class Player;
/**
 * Interface for implementing different evaluation functions.
 *
 * @author d
 */
class EvaluationFunction {
  /**
   * Method to calculate metric for moves for a player
   * at a particular stage of game to be used to select the
   * best out of possible moves for the AI player
   *
   * @param gameBoard
   * @param player
   * @return score for the current move
   */
 public:
  virtual int evaluate(const GameBoard& board, Player const* player) const = 0;
};
