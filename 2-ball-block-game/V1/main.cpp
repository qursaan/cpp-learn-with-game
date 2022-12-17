#include <iostream>     // cout, cin
#include <stdlib.h>     // system
#include <conio.h>      // getch
#include <windows.h>    // SetConsoleTextAttribute
#include <iomanip>      // setw

#define KEY_LEFT    77
#define KEY_RIGHT   75
#define GAME_WIDTH  40

using namespace std;
HANDLE cout_handle = GetStdHandle(STD_OUTPUT_HANDLE); //@V3

// @V1 to move cursor over console
void move_cursor(int col, int row)
{
  cout << "\033[" << col << ";" << row << "H";
}

// @V1 to change color between game and border
void change_color(bool isBorder){
    if(isBorder)
        SetConsoleTextAttribute(cout_handle, 2);
    else
        SetConsoleTextAttribute(cout_handle, 12);
}
// @V1 Print N of Chars in One Line
void print_nchars_line(int n, char c, bool endline=true){
    for(int i=0;i<n;++i){
        cout<<c;
    }
    if (endline)
        cout<<"\n";
}
// Print EVERY CENTER inside border
void print_centered(string str){
    int len = str.length();
    int padding = (GAME_WIDTH-len)/2;
    //set border color
    change_color(true);
    cout<<'|';
    for(int i=1; i<padding; i++){
        cout<< ' ';
    }
    change_color(false);
    cout<<str;
    //return to border color
    change_color(true);
    for(int i=len+padding; i<GAME_WIDTH-1; i++){
        cout<< ' ';
    }
    cout<<"|\n";
    change_color(false);
}

// @V1 Clear and Print Game Header contains Trial Number and Level
void game_header(int ntrial,int mtrail, int level){

    system("cls");

    change_color(true);
    //print header 50 * in line
    print_nchars_line(GAME_WIDTH,'=');

    cout << "| LIVES: " << ntrial << "/" << mtrail;
    //align level into right
    cout << setw(GAME_WIDTH-15) << "LEVEL: " << level << " |" <<endl;

    //print header 50 * in line
    print_nchars_line(GAME_WIDTH,'=');

    change_color(false);
}

// @V1 print game footer
void game_footer(){
    change_color(true);
    //print header 50 * in line
    print_nchars_line(GAME_WIDTH,'=');
    change_color(false);
}

// @V1 print game footer
void print_bar(int spaces, int barSize=5){
    //print space before
    print_nchars_line(spaces,' ',false);
    //print bar
    print_nchars_line(barSize,'^',false);
    //print space after = game width - (2 for border + bar size + space before )
    print_nchars_line(GAME_WIDTH-(barSize+spaces+2),' ',false);
}


int main()
{
    //Define Variable
    int m_trial, n_trial;
    int score;
    int level;
    int n_lines; //total number of lines
    int spaces, bar_size;

    //Initiate Variables
    m_trial     = 5;
    n_trial     = 0;
    score       = 0;
    n_lines     = 0;
    bar_size    = 5;
    spaces      = 0;


    //Show the game header
    game_header(n_trial, m_trial, level);
    //header take 3 lines
    n_lines = 3;

    //padding top
    for(int i=0; i<10; i++)
        print_centered(" ");
    n_lines+=10; //3 line paddinp

    game_footer();

    while(1)
    {
        move_cursor(n_lines,2); //move cursor back
        print_bar(spaces);
        //if(getch()!=224)
        //    continue;
        char c = getch();
        switch(getch()) {
        case KEY_RIGHT:
            if(spaces>0) spaces--;
            break;
        case KEY_LEFT:
            if(spaces<(GAME_WIDTH-bar_size-2)) spaces++;
            break;
        default:
            break;
        }
    }
    return 0;
}

