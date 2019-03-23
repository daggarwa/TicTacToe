#pragma once

#include "core/Move.h"

/**
 * Container class for returning move along with score
 * after evaluating all possible moves for AI player
 * through minimax
 *
 * @author d
 */
class SearchResult {
  /** current move*/
  Move move;

  /** score on move */
  int score;

 public:
  /**
   * Gets the score.
   *
   * @return the score
   */
  int getScore() { 
	  return score; 
  }

  /**
   * Gets the move.
   *
   * @return the move
   */
  Move getMove() { 
	  return move; 
  }

  /**
   * Returns negation of score for opponent
   * for current move
   *
   * @return the search result
   */
  SearchResult negated() { 
	  return SearchResult(move, -score); 
  }

  /**
   * Instantiates a new search result.
   *
   * @param move the move
   * @param score the score
   */
  SearchResult(Move a_move, int a_score) {
    move = a_move;
    score = a_score;
  }
};
