#include "KnightTourBoard.hpp"

#include <iomanip>
#include <iostream>

// define offsets for all 8 (row,col) pairs of knight movements
const int KnightTourBoard::KNIGHT_MOVES[8][2] = {
    {-2,-1},
    {-2,1},
    {-1,-2},
    {1,-2},
    {2,-1},
    {2,1},
    {-1,2},
    {1,2},
};

//initialization for arbitrary size
KnightTourBoard::KnightTourBoard(int size)
    : size_(size), board_(size, std::vector<int>(size, 0)), currentMoveNumber_(0) {}

KnightTourBoard::~KnightTourBoard() = default;

bool KnightTourBoard::makeMove(int row, int col) {
    // note: board_ stores
    if(!isValidMove(row,col))
    {
        std::cout << "invalid move!" << '\n';
        return(1); //return true? fix later
    }
    board_
}

bool KnightTourBoard::isValidMove(int row, int col) const {
    // note: board is represented as 2D array, (0,0) at top left corner
    // struct used to hold board information (struct fields public by default)
    //size = row = col (square)

    return(row <= board_.size() && col <= board_.size() && !isVisited(row,col));    //isVisited must be false for this to work
}

std::vector<std::pair<int, int>> KnightTourBoard::getLegalMoves(int currentRow, int currentCol) const {
    // note: should return a vector of all valid pairs from the current location
}

int KnightTourBoard::countLegalMoves(int row, int col) const {
    // TODO: implement countLegalMoves to return the number of legal moves from the given position
    
}

void KnightTourBoard::reset() {
    currentMoveNumber_ = 0;
    for (auto& row : board_) {
        std::fill(row.begin(), row.end(), 0);
    }
}

void KnightTourBoard::display() const {
    const int maxVal = size_ * size_;
    const int cellWidth = std::max<int>(2, std::to_string(maxVal).size());

    std::cout << "\n     ";
    for (int col = 0; col < size_; ++col) {
        std::cout << std::setw(cellWidth + 1) << col;
    }
    std::cout << '\n';

    const int borderWidth = (cellWidth + 2) * size_;
    std::cout << "   +" << std::string(borderWidth, '-') << "+\n";

    for (int row = 0; row < size_; ++row) {
        std::cout << std::setw(3) << row << " |";
        for (int col = 0; col < size_; ++col) {
            std::string cellRep;
            if (board_[row][col] == 0) {
                cellRep = ".";
            } else if (board_[row][col] == currentMoveNumber_) {
                cellRep = "K";
            } else {
                cellRep = std::to_string(board_[row][col]);
            }
            std::cout << " " << std::setw(cellWidth) << cellRep;
        }
        std::cout << " |\n";
    }

    std::cout << "   +" << std::string(borderWidth, '-') << "+\n";
}

bool KnightTourBoard::isVisited(int row, int col) const {
    // TODO: implement isVisited to check if the given position has been visited
    
}

int KnightTourBoard::getMoveNumber(int row, int col) const {
    return board_[row][col];
}