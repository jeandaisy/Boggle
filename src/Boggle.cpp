// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "bogglegui.h"
#include <shuffle.h>
#include <algorithm>
#include <string>


// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

const int MIN_BOGGLE_SIZE = 4;
/*In this constructor you initialize  your Boggle board to use the given dictionary lexicon to look up words,
 * and use the given 16-letter string to initialize the 16 board cubes from top-left to bottom-right.
 * if the string is empty, you should generate a random shuffled board. Your method should be case-insensitive,
 * it should accept the board text whether it is passed in upper, lower, or mixed case.
 */
void Boggle::ramdomBoard(){
    board.resize(MIN_BOGGLE_SIZE,MIN_BOGGLE_SIZE);
    int cube_array[16] = {0, 1, 2, 3 ,4, 5, 6, 7, 8, 9, 10, 11,12,13,14,15};
    int side_array[6] = {0, 1, 2, 3, 4, 5};
    shuffle(cube_array,16);

    for(int i = 0; i < 16; i++){
        int m = cube_array[i];
        string S = CUBES[m];
        shuffle(side_array,6);
        int side_number = side_array[0];
        char letter = S[side_number];
        board.set(i/4,i%4, letter);
        BoggleGUI::labelCube(i/4,i%4, letter,false);
    }

}
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
//    *dict = dictionary;
    dict = &dictionary;
    BoggleGUI::initialize(MIN_BOGGLE_SIZE,MIN_BOGGLE_SIZE);

}
void Boggle::set_board(string letters16){

    board.resize(MIN_BOGGLE_SIZE,MIN_BOGGLE_SIZE);
    BoggleGUI::initialize(MIN_BOGGLE_SIZE,MIN_BOGGLE_SIZE);
    clearConsole();

    for(int i = 0; i<MIN_BOGGLE_SIZE; i++){
        for(int j = 0; j < MIN_BOGGLE_SIZE; j++){
            int index = MIN_BOGGLE_SIZE*i + j;
            board[i][j] = letters16[index];
            BoggleGUI::labelCube(i, j, letters16[index], false);
        }
    }
}

/* In this function you should return the char that is stored in your Boggle board at the given 0-based row
 * and column. If the row and/or column are out of bounds, you should throw an int exexception
 */
char Boggle::getLetter(int row, int col) {
    // TODO: implement
    if( row < 0|| row >= MIN_BOGGLE_SIZE ){
        throw(row);
    }
    if( col < 0 || col >= MIN_BOGGLE_SIZE ){
        throw(col);
    }
    char result = this->board.get(row, col);
    return result;
}
/* In this function, you should check whether the given word string is suitable to search for on the board:
 * that is, whether it is in the dictionary, long enough to be a valid Boggle word, and hs not already been
 * found. You should return a boolean result of true if the word is suitable and otherwise you should return
 * false. Your method should be case-insensitive, you should properly verify the word whethere it is passed
 * in upper lower, or mixed case
 */
bool Boggle::checkWord(string word) {
    transform(word.begin(),word.end(),word.begin(),::tolower);
    if(word.length() < 4)
       return false;

    if(!dict->contains(word))
        return false;

    if(dict_human->contains(word))
        return false;

    return true;
}
bool Boggle::humanWordSearchHelper(string word, Grid<bool> mark, int row, int col){
    //base case

    if(word.empty() ) return true;
    if( (row < 0) || (row >= MIN_BOGGLE_SIZE) ) return false;
    if( (col < 0) || (col >= MIN_BOGGLE_SIZE) ) return false;
    if(tolower(board[row][col]) != tolower(word[0]) || mark[row][col] == true) return false;

    else{
        mark[row][col] = true;
        word = word.erase(0,1);
        BoggleGUI::setHighlighted(row,col, true);
        if( humanWordSearchHelper(word,mark,row,col+1) ) return true;
        if( humanWordSearchHelper(word,mark,row,col-1) ) return true;
        if( humanWordSearchHelper(word,mark,row-1,col+1) ) return true;
        if( humanWordSearchHelper(word,mark,row-1,col-1) ) return true;
        if( humanWordSearchHelper(word,mark,row-1,col) ) return true;
        if( humanWordSearchHelper(word,mark,row+1,col-1) ) return true;
        if( humanWordSearchHelper(word,mark,row+1,col+1) ) return true;
        if( humanWordSearchHelper(word,mark,row+1,col) ) return true;
    }
    BoggleGUI::setHighlighted(row,col, false);
    return false;
}
bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    transform(word.begin(),word.end(),word.begin(),::tolower);
    Grid<bool> mark = Grid<bool>(4,4,false);
    string w = word;
    for(int i = 0; i < MIN_BOGGLE_SIZE;i++){
        for(int m = 0; m < MIN_BOGGLE_SIZE; m++){
            if(humanWordSearchHelper(w,mark,i,m)) return true;
        }
    }
    return false;
}
void Boggle::print_board(){
    int counter = 0;
    for(auto i:board){
        cout<<i;
        counter++;
        if(counter%4==0)cout<<endl;
    }
}
void Boggle::print_human_dict(){
    Lexicon::iterator i;
    for(i = (*dict_human).begin();i!=(*dict_human).end();i++){
        if(i!=(*dict_human).begin()){
            cout<<"\", ";
        }else{
            cout<<"\"";
        }
        cout<<*i<<"\"";
    }

}
void Boggle::gui_human_summary(){
    cout << "Your words ("<<human_count<<"): {";
    print_human_dict();
    cout<<"}"<<endl;
    cout << "Your scores : ";
    cout << human_score <<endl;
    cout <<"Type a word (or Enter to stop): ";

}
void Boggle::human_turn(){
    cout<<"It's your turn"<<endl;
    gui_human_summary();
    string human_input;
    while(true){
       getline(cin,human_input);
       BoggleGUI::clearHighlighting();
       if(human_input.empty()) break;

       if(!checkWord(human_input)){
           BoggleGUI::playSound("./../res/moo.wav");
           clearConsole();
           cout<<"You must enter an unfound 4+ letter word from the dictionary."<<endl;
           print_board();
           gui_human_summary();
           continue;
       }

       if(!humanWordSearch(human_input)){
           BoggleGUI::playSound("./../res/moo.wav");
           clearConsole();
           cout<<"That word can't be formed on this board."<<endl;
           print_board();
           gui_human_summary();
           continue;
         }

       clearConsole();
       cout<<"You found a new word! "<<"\""<<human_input<<"\""<<endl;
       BoggleGUI::playSound("./../res/tinkerbell.wav");
       print_board();
       human_scored(human_input);
       gui_human_summary();

    }

    return;
}
void Boggle::human_scored(string word){
    if( checkWord(word) && humanWordSearch(word)){
        dict_human->add(word);
        human_count++;
        human_score = human_score + word.length()-3;
    }
}


int Boggle::getScoreHuman() {
    // TODO: implement

    Lexicon::iterator i;
    for(i=dict_human->begin();i!=dict_human->end();i++)

        human_score = human_score + (*i).length()-3;
    return (int) human_score;
}

void Boggle::computerWordSearchHelper(int row, int col, string s, Grid<bool> mark){

    //base case
    if(!dict->containsPrefix(s)) return;
    if( (row < 0) || (row >= MIN_BOGGLE_SIZE) ) return;
    if( (col < 0) || (col >= MIN_BOGGLE_SIZE) ) return;
    if(s.length() >= 8) return;
    if(mark[row][col]==true) return;
    s.push_back(board[row][col]);
    mark[row][col] = true;

    if(dict->contains(s) && (!dict_human->contains(s))
            && (!dict_machine->contains(s)) && s.length() >=4){
        dict_machine->add(s);
        machine_count++;
    }

    computerWordSearchHelper(row, col-1,s,mark);
    computerWordSearchHelper(row, col+1,s,mark);
    computerWordSearchHelper(row-1, col-1,s,mark);
    computerWordSearchHelper(row-1, col,s,mark);
    computerWordSearchHelper(row-1, col+1,s,mark);
    computerWordSearchHelper(row+1, col-1,s,mark);
    computerWordSearchHelper(row+1, col,s,mark);
    computerWordSearchHelper(row+1, col+1,s,mark);

    return;
}
Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;

    Grid<bool> mark = Grid<bool>(4,4,false);
    for(int i = 0; i < MIN_BOGGLE_SIZE;i++){
        for(int m = 0; m < MIN_BOGGLE_SIZE; m++){
            string w;
            computerWordSearchHelper(i,m,w,mark);
        }
    }

    Lexicon::iterator i;
    for(i = (*dict_machine).begin();i!=(*dict_machine).end();i++){
        result.add(*i);
    }


    return result;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    Lexicon::iterator i;
    for(i=dict_machine->begin();i!=dict_machine->end();i++)

        machine_score = machine_score + (*i).length()-3;
    return (int) machine_score;
}

void Boggle::gui_computer_summary(){
    cout<<"It's my turn!"<<endl;

    Lexicon::iterator i;
    cout<<"My words ("<<dict_machine->size()<<"): {";
    for(i = dict_machine->begin(); i!=dict_machine->end();i++){
        if(i!=dict_machine->begin())cout<<", ";
        cout<<"\""<<*i<<"\"";
    }
    cout<<"}"<<endl;
    cout<<"My score: "<<machine_score<<endl;
}



ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
