#include "core/Player.h"

Player::Player(BoardSquareState const& playerSymbol, PlayerType type_)
    : m_playerSymbol(playerSymbol), m_type(type_) {}

Player const* Player::opponent() const {
  return this->m_playerSymbol == BoardSquareState::CROSS ? NOUGHT.get()
                                                         : CROSS.get();
}

bool Player::operator==(const Player& rhs) const {
  return this->m_playerSymbol == rhs.m_playerSymbol;
}

PlayerType Player::type() const { return m_type; }

BoardSquareState Player::playerSymbol() const { return m_playerSymbol; }

std::string Player::toString() const { return stateToString(m_playerSymbol); }

std::ostream& operator<<(std::ostream& Str, Player const& v) {
  Str << stateToString(v.m_playerSymbol);
  return Str;
}
