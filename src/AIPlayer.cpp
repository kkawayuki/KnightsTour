#include "AIPlayer.hpp"

#include <algorithm>

AIPlayer::AIPlayer()
{
    resetStats();
}

AIPlayer::~AIPlayer() = default;

const char *AIPlayer::name() const
{
    return "Warnsdorff AI";
}

void AIPlayer::resetStats()
{
    Player::resetStats();
}

// implement calculateWarnsdorffScore to return the number of legal moves from the given position
double AIPlayer::calculateWarnsdorffScore(const KnightTourBoard &board, int row, int col) const
{
    return (board.countLegalMoves(row, col));
}

// implement scoreMoves to return a vector of ScoredMove objects
// for the legal moves at the current position
std::vector<ScoredMove> AIPlayer::scoreMoves(
    const KnightTourBoard &board,
    const std::vector<std::pair<int, int>> &legalMoves) const
{
    std::vector<ScoredMove> scoredMovesVec;

    // has all legalMoves, now needs to itearate through and score each one
    for (int i = 0; i < legalMoves.size(); i++)
    {
        ScoredMove temp;
        temp.row = legalMoves[i].first; // use pair notation for referencing
        temp.col = legalMoves[i].second;
        temp.score = calculateWarnsdorffScore(board, temp.row, temp.col); // use current stored to calculate warnsdorff

        scoredMovesVec.push_back(temp);
    }
    return (scoredMovesVec);
}

// Implement the AI player tour solver
// 1. Initialize the board and stats
// 2. Loop until the tour is complete or maxMoves is reached
// 3. Set the summary fields based on the results
SolveSummary AIPlayer::solveTour(KnightTourBoard &board, int startRow, int startCol, int maxMoves)
{
    SolveSummary summary;
    resetStats();
    board.reset();

    std::vector<ScoredMove> currScored;
    int currRow = startRow;
    int currCol = startCol;
    std::vector<int> bstHeights;
    std::vector<int> llrbHeights;
    int bstTotalHeight = 0;
    int llrbTotalHeight = 0;

    board.makeMove(currRow, currCol); // make initial move to center of board

    while (board.getMoveNumber(currRow, currCol) < maxMoves)
    {
        // create trees for current loop
        BinaryTree<ScoredMove> bstTree(BinaryTree<ScoredMove>::TreeType::BST);
        BinaryTree<ScoredMove> llrbTree(BinaryTree<ScoredMove>::TreeType::LLRB);

        currScored = scoreMoves(board, board.getLegalMoves(currRow, currCol)); // get vector of scored moves

        for (int j = 0; j < currScored.size(); j++) // populate each search tree with all possible moves
        {
            bstTree.insert(currScored[j]);
            llrbTree.insert(currScored[j]);
        }

        // find and execute move with smallest warnsdorff score, update position current
        const ScoredMove *min = bstTree.findMin();
        if (min == nullptr)
            break;
        board.makeMove(min->row, min->col);
        currRow = min->row;
        currCol = min->col;

        // track tree heights/performance metrics
        bstHeights.push_back(bstTree.getHeight());
        llrbHeights.push_back(llrbTree.getHeight());

        int currentIndex = bstHeights.size() - 1;
        if (bstHeights[currentIndex] > summary.bstMaxHeight)
            summary.bstMaxHeight = bstHeights[currentIndex];
        if (llrbHeights[currentIndex] > summary.llrbMaxHeight)
            summary.llrbMaxHeight = llrbHeights[currentIndex];
    }

    // calculate total from vectors
    for (int i = 0; i < bstHeights.size(); i++)
        bstTotalHeight += bstHeights[i];
    for (int i = 0; i < llrbHeights.size(); i++)
        llrbTotalHeight += llrbHeights[i];

    // finish setting summary fields
    summary.maxPossibleMoves = board.getSize() * board.getSize();
    summary.solved = (board.getMoveNumber(currRow, currCol) == summary.maxPossibleMoves);
    if (bstHeights.size() != 0)
    {
        summary.bstAverageHeight = bstTotalHeight / bstHeights.size();
        summary.llrbAverageHeight = llrbTotalHeight / llrbHeights.size();
    }
    return summary;
}