#pragma once
/**
* The Class BoardStats.
* Maintains counts for board square states
* as per each player's move on the game board. 
*
* @author d
*/
class BoardStats {
public:
	std::vector<std::array<size_t, 3>> rowCounts;
	std::vector<std::array<size_t, 3>> colCounts;
	std::array<size_t, 3> diagCounts;
	std::array<size_t, 3> revDiagCounts;

	BoardStats() {
		rowCounts.resize(GameConstants::SIZE, std::array<size_t, 3>({ 0 }));
		colCounts.resize(GameConstants::SIZE, std::array<size_t, 3>({ 0 }));
		diagCounts = std::array<size_t, 3>({ 0 });
		revDiagCounts = std::array<size_t, 3>({ 0 });
	}

};