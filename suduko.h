#ifndef _SUDUKO_H
#define _SUDUKO_H

#include <string>
#include <fstream>

class Suduko {
public:
    Suduko();
    Suduko(std::string sudu);

    void pretty_print();
    void init();

    int get_element_index(int index);
    int get_element(int row, int col);

    void set_element_index(int index, int element);
    void set_element(int row, int col, int element);
    
    bool isOK(int row, int col, int value);
        
    bool solve(); // solve the puzzle
    bool backtrace(int index);
    void gen_puzzle(); // generate random puzzle
    
private:
    const int ROWSIZE = 9;
    const int COLSIZE = 9;
    const int BLOCKSIZE = 3;
    
    int elements[9][9];
    int elements_init[9][9];
};

#endif
