#include "suduko.h"
#include<stdexcept>
#include<sstream>
#include<iostream>

Suduko::Suduko()
{
    for (int i = 0; i < ROWSIZE; i++)
        for (int j = 0; j < COLSIZE; j++) {
            elements[i][j] = 0;
            elements_init[i][j] = 0;
        }

}

Suduko::Suduko(std::string sudu)
{
    if (sudu.length() < 81)
        throw std::runtime_error("string input out of range");
 
    for (int i=0; i<ROWSIZE*COLSIZE; i++) {
        int value = sudu[i]-'0';
        int row = i / 9;
        int col = i % 9;
        elements[row][col] = value;
        elements_init[row][col] = value;
    }
}

void Suduko::pretty_print()
{
    for (int i = 0; i < ROWSIZE; i++) {
        if (i % 3 == 0) {
            std::cout << " -----------------------\n";
        }
        for (int j = 0; j < COLSIZE; j++) {
            if (j % 3 == 0) {
                std::cout << "| ";
            }
            std::cout << elements[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " -----------------------\n";
}


void Suduko::gen_puzzle()
{
    
}

// row,col: 0-8,0-8   check whether value can be assigned at (row,col)
bool Suduko::isOK(int row, int col, int value)
{
    // the same row
    for (int i = 0; i < COLSIZE; i++) {
        if (elements[row][i]==value && i!=col) return false;
    }

    // the same column
    for (int i = 0; i < ROWSIZE; i++) {
        if (elements[i][col]==value && i!=row) return false;
    }

    // the same block
    // topleft coordinates of the grid
    int topleft_row = row/BLOCKSIZE*BLOCKSIZE;
    int topleft_col = col/BLOCKSIZE*BLOCKSIZE;
    
    
    for (int i = topleft_row; i < topleft_row+BLOCKSIZE; i++) {
        for (int j = topleft_col; j < topleft_col+BLOCKSIZE; j++) {
            if (elements[i][j] == value && (i!=row) && (j!=col))
                return false;
        }
    }

    return true;
}


bool Suduko::solve()
{
    return backtrace(0);
}


bool Suduko::backtrace(int index)
{
    if (index >= ROWSIZE*COLSIZE) {
        return true;
    }

    int row = index / ROWSIZE;
    int col = index % COLSIZE;

    if (0 != elements[row][col]) {
        return backtrace(index+1);
    }

    else {
        for (int i = 1; i <= 9; i++) {
            elements[row][col] = i;
            if (isOK(row, col, i)) {
                if (backtrace(index+1))
                    return true;
            }
            elements[row][col] = 0; //backtrace
        }
        return false;
    }
}


// from 1-81
int Suduko::get_element_index(int index)
{
    if (!(index>=1&&index<=ROWSIZE*COLSIZE))
        throw std::runtime_error("index out of range");
    int row = (index-1) / 9;
    int col = (index-1) % 9;

    return elements[row][col];
}

//9*9
int Suduko::get_element(int row, int col)
{
    if (!(row>=0&&row<ROWSIZE))
        throw std::runtime_error("row out of range");
    if (!(col>=0&&col<COLSIZE))
        throw std::runtime_error("column out of range");

    return elements[row][col];
}

// from 1-81
void Suduko::set_element_index(int index, int element)
{
    if (!(element>=0&&element<=9))
        throw std::runtime_error("element out of range");
    if (!(index>=1&&index<=ROWSIZE*COLSIZE))
        throw std::runtime_error("index out of range");

    int row = (index-1) / 9;
    int col = (index-1) % 9;

    elements[row][col] = element;
}

//9*9
void Suduko::set_element(int row, int col, int element)
{
    if (!(element>=0&&element<=9))
        throw std::runtime_error("element out of range");
    if (!(row>=0&&row<ROWSIZE))
        throw std::runtime_error("row out of range");
    if (!(col>=0&&col<COLSIZE))
        throw std::runtime_error("column out of range");
    
    elements[row][col] = element;
}

void Suduko::init()
{
    for (int i = 0; i < ROWSIZE; i++)
        for (int j = 0; j < COLSIZE; j++) {
            elements[i][j] = elements_init[i][j];
        }
}



