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

//implement calculateWarnsdorffScore to return the number of legal moves from the given position
double AIPlayer::calculateWarnsdorffScore(const KnightTourBoard& board, int row, int col) const {
    return(board.countLegalMoves(row,col)); 
}

// implement scoreMoves to return a vector of ScoredMove objects 
// for the legal moves at the current position
std::vector<ScoredMove> AIPlayer::scoreMoves(
    const KnightTourBoard& board,
    const std::vector<std::pair<int, int>>& legalMoves) const {
    std::vector<ScoredMove> scoredMovesVec; 
    
    //has all legalMoves, now needs to itearate through and score each one
    for(int i = 0; i < legalMoves.size(); i++)
    {
        ScoredMove temp; 
        temp.row = legalMoves[i].first;    //use pair notation for referencing
        temp.col = legalMoves[i].second;
        temp.score = calculateWarnsdorffScore(board, temp.row, temp.col);  //use current stored to calculate warnsdorff

        scoredMovesVec.push_back(temp); 
    }
    return(scoredMovesVec); 
}

// Implement the AI player tour solver
// 1. Initialize the board and stats
// 2. Loop until the tour is complete or maxMoves is reached
// 3. Set the summary fields based on the results
SolveSummary AIPlayer::solveTour( KnightTourBoard& board, int startRow, int startCol, int maxMoves) {
    SolveSummary summary;
    resetStats();
    board.reset();

    int currRow = startRow;
    int currCol = startCol;
    board.makeMove(currRow, currCol);
    std::vector<ScoredMove> currScored; 
    
    //may need to reimplement to use BST 
    while(board.getMoveNumber(currRow, currCol) < maxMoves)
    {
        currScored = scoreMoves(board, board.getLegalMoves(currRow, currCol)); //get vector of scored moves

        //move scored into BST/LLRB tree
        //Select the minimum scored move from BST.
        //Track tree heights and performance metrics.
        //Repeat until the tour is complete or no moves remain.

    }

    //game completion
    
    //set summary fields
    
    return summary;
}