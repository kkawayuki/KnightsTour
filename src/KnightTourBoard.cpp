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
    : size_(size), board_(size, std::vector<int>(size, 0)), currentMoveNumber_(0) {}    //initialization sets initial values to zero

KnightTourBoard::~KnightTourBoard() = default;


//makeMove function should update board, update isVisited, add to move counter
bool KnightTourBoard::makeMove(int row, int col) { 
    if(!isValidMove(row,col)) //error case
        return(0); 

    board_[row][col] = ++currentMoveNumber_; //store currentMoveNumber as int 
    return(true);             
}

bool KnightTourBoard::isValidMove(int row, int col) const {
    Position current(row,col);  //use to temp store current locations
    return(current.isValid(this->getSize()) && !isVisited(row,col));    //use position and visited checker 
}

// note: should return a vector of all valid pairs from the current location
std::vector<std::pair<int, int>> KnightTourBoard::getLegalMoves(int currentRow, int currentCol) const {
    std::vector<std::pair<int, int>> validMoves;

    if(!Position(currentRow,currentCol).isValid(size_)) //error case
        return(validMoves);
    
    for(int i = 0; i < 8; i++)      //using magic number due to 8 possible moves from knight
    {
        if(isValidMove(currentRow + KNIGHT_MOVES[i][0], currentCol + KNIGHT_MOVES[i][1]))   //if offset is valid
        {
            std::pair<int,int> tempValid = {currentRow + KNIGHT_MOVES[i][0], currentCol + KNIGHT_MOVES[i][1]}; 
            validMoves.push_back(tempValid);
        }
    }
    return(validMoves); 
}

int KnightTourBoard::countLegalMoves(int row, int col) const {
    if(!Position(row,col).isValid(size_))
        return(0);

    std::vector<std::pair<int, int>> validMoves = getLegalMoves(row,col); 
    return(validMoves.size()); 
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

//note: if visited, has nonzero value depending on move number
bool KnightTourBoard::isVisited(int row, int col) const {
    if(!Position(row,col).isValid(size_))
        return(false);

    return(board_[row][col] != 0); 
}

int KnightTourBoard::getMoveNumber(int row, int col) const {
    if(!Position(row,col).isValid(size_))
        return(0);
        
    return board_[row][col];
}