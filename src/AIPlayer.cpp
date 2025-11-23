#include "AIPlayer.hpp"

#include <algorithm>

AIPlayer::AIPlayer() {
    resetStats();
}

AIPlayer::~AIPlayer() = default;

const char* AIPlayer::name() const {
    return "Warnsdorff AI";
}

void AIPlayer::resetStats() {
    Player::resetStats();
}

double AIPlayer::calculateWarnsdorffScore(const KnightTourBoard& board, int row, int col) const {
    // TODO: implement calculateWarnsdorffScore to return the number of legal moves from the given position
    
}

std::vector<ScoredMove> AIPlayer::scoreMoves(
    const KnightTourBoard& board,
    const std::vector<std::pair<int, int>>& legalMoves) const {
    // TODO: implement scoreMoves to return a vector of ScoredMove objects 
    // for the legal moves at the current position
    
    
}

SolveSummary AIPlayer::solveTour(
    KnightTourBoard& board, int startRow, int startCol, int maxMoves) {
    SolveSummary summary;
    resetStats();
    board.reset();

    // TODO: implement the AI player tour solver
    // 1. Initialize the board and stats
    // 2. Loop until the tour is complete or maxMoves is reached
    // 3. Set the summary fields based on the results

    
    return summary;
}