#pragma once

class SearchResult;
class GameBoard;
class Player;
class EvaluationFunction;
/**
 * Interface for simple searcher without alpha beta pruning
 *
 * @author d
 */
class SimpleSearcher {
  /**
   * Simple search.
   *
   * @param gameBoard
   * @param current player
   * @param depth i.e. number of look ahead moves
   * @param evaluation function
   * @return the search result
   */
  virtual SearchResult simpleSearch(const GameBoard &board,
                                    Player const *player, const int depth,
                                    const EvaluationFunction &function) = 0;
};
