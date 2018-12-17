// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    bool humanWordSearchHelper(string word, Grid<bool> mark, int row, int col);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    void human_scored(string word);
    void print_board();
    void human_turn();
    void print_human_dict();
    void print_machine_dict();
    void gui_human_summary();

    void computerWordSearchHelper(int row, int col,string s,Grid<bool> mark);
    void gui_computer_summary();
    void set_board(string letters16);


    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    void ramdomBoard();
private:
    // TODO: add any other member functions/variables necessary
    Grid<char> board;
    Lexicon* dict;
    Lexicon* dict_human = new Lexicon;
    Lexicon* dict_machine = new Lexicon;

    unsigned long human_score = 0;
    unsigned long human_count = 0;
    unsigned long machine_count = 0;
    unsigned long machine_score = 0;

};

#endif // _boggle_h
