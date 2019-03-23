#pragma once

#include <string>
/**
 * Denotes type of difficulty levels in the game
 *
 * @author d
 */
enum class DifficultyLevel {

  /** Small description for the level */
  /** Easy level */
  EASY = 3,
  /** Normal level */
  NORMAL = 4,

  /** Hard level */
  HARD = 5,

  /** Heroic level */
  HEROIC = 6,

  MAX = 9
};
