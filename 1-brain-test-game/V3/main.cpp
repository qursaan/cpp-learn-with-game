#include <iostream>     // cout, cin
#include <stdlib.h>     // rand, srand, system
#include <unistd.h>     // sleep
#include <time.h>       // time.now time_t
#include <conio.h>      // getch
#include <iomanip>      // setw#include <iomanip>      // setw
#include <string.h>     // string var
#include <windows.h>    // SetConsoleTextAttribute
using namespace std;

HANDLE cout_handle = GetStdHandle(STD_OUTPUT_HANDLE); //@V3

// @V3 to move cursor over console
void moveCursor(std::ostream& os, int col, int row)
{
  os << "\033[" << col << ";" << row << "H";
}
// @V3 to change color between game and border
void change_color(bool isBorder){
    if(isBorder)
        SetConsoleTextAttribute(cout_handle, 2);
    else
        SetConsoleTextAttribute(cout_handle, 12);
}
// @V3
void print_centered(string str, int width){
    int len = str.length();
    int padding = (width-len)/2;
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
    for(int i=len+padding; i<width-1; i++){
        cout<< ' ';
    }
    cout<<"|\n";
    change_color(false);
}

// @V2 Print N of Chars in One Line
void print_nchars_line(int n, char c){
    for(int i=0;i<n;++i){
        cout<<c;
    }
    cout<<"\n";
}

// @V2 Clear and Print Game Header contains Trial Number and Level
void game_header(int ntrial,int mtrail, int level){

    system("cls");

    change_color(true);
    //print header 50 * in line
    print_nchars_line(50,'-');


    cout << "| Trial: " << ntrial << "/" << mtrail;
    //align level into right
    cout << setw(35) << "Level: " << level << " |" <<endl;

    //print header 50 * in line
    print_nchars_line(50,'-');

    change_color(false);
}

// @V3 print game footer
void game_footer(){
    change_color(true);
    //print header 50 * in line
    print_nchars_line(50,'-');
    change_color(false);
}

// @V2 Print a waiting message with count down N Seconds
void start_after(int sec){
    cout<< "\n\t\tStart in ";
    for(int i=sec; i>0; i--){
        cout << i << "s...";
        sleep(1);
        cout <<"\b\b\b\b\b";
    }
}

// @V2 Print and Get user Level number
int get_user_level(){
    int level;
    cout << "\nChoose Challenge Level [1-3]:\n -1- Easy\n -2- Medium\n -3- Hard\n> ";
    cin >> level;
    while(level > 3 || level < 1){
        cout<< "Enter a valid level [1-3]: ";
        cin >> level;
    }
    cout << "YOU CHOOSE " << (level==1?"EASY":level==2?"MEDIUM":"HARD") << " LEVEL :)\n";
    return level;
}


int main()
{
    //0a. Define Variable
    int m_trial, n_trial;
    int score, g_timeout;
    int width, length;
    int area , user_area;
    int table_size;
    time_t user_stime, user_timeout;
    int level;
    int game_width;
    int n_lines; //total number of lines

    //1a. Initiate Variables
    game_width  = 50;
    table_size  = 5;
    m_trial     = 5;
    n_trial     = 0;
    score       = 0;
    n_lines     = 0;
    //0c. Change random based on time
    srand(time(0));

    //0b. Print Game instructions
    print_nchars_line(game_width,'-');
    cout << "|\t Welcome to my first Game :)\t\t |\n";
    cout << "|Vision Shape and Cal. its Area in a few seconds.|\n";
    print_nchars_line(game_width,'-');
    system("pause");// @V3

    //@V2 Get user level and store in local variable.
    level = get_user_level();

    do{
        //@V2 Start game after 3 second
        start_after(1);
        //------Initiate Variables repeated part
        //@V2 Set tablesize and timeout based on level
        width       = (2*level)+rand()%(table_size+(level-1)*2);
        length      = (2*level)+rand()%(table_size+(level-1)*2);
        g_timeout   = 6-level;
        area        = width * length;
        n_trial++;

        //@V2 Show the game header
        game_header(n_trial, m_trial, level);
        //header take 3 lines
        n_lines = 3;

        //2b. padding top
        for(int i=0; i<3; i++)
            print_centered(" ",game_width);
        n_lines+=3; //3 line padding

        //2a. Draw the Rectangle
        string rect_line= "";
        //@V3 get one line
        for(int j=0; j<width; j++){
            rect_line += "# ";
        }
        //@V3 print line multiple times
        for(int i=0;i<length;i++){
            print_centered(rect_line, game_width);
            ++n_lines;
        }

        //3c. Set Start time
        user_stime = time(0);

        for(int i=0; i<3; i++)
            print_centered(" ",game_width);
        n_lines+=3; //3 line padding

        //3a. Ask User
        print_centered("Area = ", game_width);
        int answer_inLine = ++n_lines; // get the line of answer
        game_footer();

        moveCursor(std::cout, answer_inLine,29); //move cursor back to answer line

        cin >>user_area;
        //3c. Set end time and calc diff
        user_timeout = time(0) - user_stime;
        print_centered("You take " + to_string(user_timeout)+ "s to answer!....", game_width);

        //4a. Compare Answer and Give them point
        if(user_area==area && user_timeout <= g_timeout){
            score++;
            print_centered("Correct :)",game_width);
        }else if(user_area!= area){
            print_centered("Wrong :( ",game_width);
        }else {
            print_centered("Timeout :|, try fast",game_width);
        }
        game_footer();
    }
    //5a. Check the number of trial
    while(n_trial<m_trial);

    game_header(n_trial, m_trial, level);
    //6a. Game over and print socre
    cout<<"\n\t\tGAME OVER\n";
    cout<<"\n\t\tYour Score is :" <<(score*1.0/m_trial)*100.0 <<"%\n";
    game_footer();
    return 0;
}
