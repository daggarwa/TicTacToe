#include "core/Player.h"

Player::Player(BoardSquareState const& playerSymbol)
    : m_playerSymbol(playerSymbol) {}

Player Player::opponent() const { return (*this) == CROSS ? NOUGHT : CROSS; }

bool Player::operator==(const Player& rhs) const {
  return this->m_playerSymbol == rhs.m_playerSymbol;
}

BoardSquareState Player::playerSymbol() const { return m_playerSymbol; }

std::string Player::toString() const { return stateToString(m_playerSymbol); }

std::ostream& operator<<(std::ostream& Str, Player const& v) {
  Str << stateToString(v.m_playerSymbol);
  return Str;
}
