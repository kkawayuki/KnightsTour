#ifndef SCOREDMOVE_HPP
#define SCOREDMOVE_HPP

struct ScoredMove {
    int row;
    int col;
    double score;

    ScoredMove() : row(-1), col(-1), score(0.0) {}
    ScoredMove(int r, int c, double s) : row(r), col(c), score(s) {}

    // implemented comparison operators for sorting, 
    // if score is the same, break ties by row and then column
    bool operator<(const ScoredMove& other) const 
    {  
        if(this->score < other.score) return true;
        if(this->score > other.score) return false;
        
        if(this->row < other.row) return true;
        if(this->row > other.row) return false;
        
        return(this->col < other.col); 
    }

    bool operator>(const ScoredMove& other) const 
    {
        if(this->score > other.score) return true;
        if(this->score < other.score) return false;
        
        if(this->row > other.row) return true;
        if(this->row < other.row) return false;
        
        return(this->col > other.col); 
    }

    bool operator==(const ScoredMove& other) const // revise? 
    { 
        return(this->score == other.score && this->row == other.row && this->col == other.col); 
    }

    bool operator!=(const ScoredMove& other) const { return !(*this == other); }
};

#endif // SCOREDMOVE_HPP