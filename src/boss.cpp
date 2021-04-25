#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "boss.h"

using namespace std;

void mvw_print_file(WINDOW* WIN,string file_loc, int y, int x){
    ifstream fin;
    fin.open(file_loc);
    string str;
    while(getline(fin, str)){
       mvwprintw(WIN,y,x,str.c_str()); 
       y++;
    }
    fin.close();
}

void printBoss(WINDOW* WIN){

    mvw_print_file(WIN, "src/boss.txt", 4, 40);
    
}
