// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "shuffle.h"
#include "simpio.h"
#include "bogglegui.h"

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    Boggle B(dictionary,"");


        bool random = getYesOrNo("Do you want to generate a random board? ");
        if(random){
            B.ramdomBoard();
        }else{
            while(1){
                cout<<"Type the 16 letters to appear on the board: ";
                string board_letters;
                getline(cin, board_letters);
                if(board_letters.length()!=16){
                    cout<<"That is not a valid 16-letter board string. Try again."<<endl;
                    continue;
                }

                for(int i = 0; i < 16; i++){
                    if(!isalpha(board_letters[i])){
                        cout<<"That is not a valid 16-letter board string. Try again."<<endl;
                        continue;
                    }
                }

                B.set_board(board_letters);
                break;
            }

        }


/*
        // for testing purpose
        string test_case1 = "WLWAOKSEMONAUETA";
        string test_case2 = "OUVOOOZEDHHEJDKT";
        B.set_board(test_case2);
*/

        B.human_turn();
        B.computerWordSearch();
        B.gui_computer_summary();

        if(B.getScoreComputer()>B.getScoreHuman()){
            cout<<"Ha ha ha, I destroyed you. Better luck next time, puny human!"<<endl;
            BoggleGUI::playSound("./../res/thats-pathetic.wav");
        }



}
