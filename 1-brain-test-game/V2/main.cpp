#include <iostream>     // cout, cin
#include <stdlib.h>     // rand, srand, system
#include <unistd.h>     // sleep
#include <time.h>       // time.now time_t
#include <conio.h>      // getch
#include <iomanip>      // setw

using namespace std;

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
    //print header 50 * in line
    print_nchars_line(50,'-');

    cout << "| Trial: " << ntrial << "/" << mtrail;
    //align level into right
    cout << setw(35) << "Level: " << level << " |" <<endl;

    //print header 50 * in line
    print_nchars_line(50,'-');
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


    //1a. Initiate Variables
    table_size  = 5;
    m_trial     = 5;
    n_trial     = 0;
    score       = 0;
    //0c. Change random based on time
    srand(time(0));

    //0b. Print Game instructions
    print_nchars_line(50,'-');
    cout << "|\t Welcome to my first Game :)\t\t |\n";
    cout << "|Vision Shape and Cal. its Area in a few seconds.|\n";
    print_nchars_line(50,'-');
    cout << "\n\nPress Any to start playing ...";
    getch(); //<- @V2 correct this line

    //@V2 Clear hole above line from output
    cout <<"\r\t\t\t\t\t\t";
    //@V2 Get user level and store in local variable.
    level = get_user_level();

    //@V2 Start game after 3 second
    start_after(3);

    do{
        //------Initiate Variables repeated part
        //@V2 Set tablesize and timeout based on level
        width       = (2*level)+rand()%(table_size+(level-1)*2);
        length      = (2*level)+rand()%(table_size+(level-1)*2);
        g_timeout   = 6-level;
        area        = width * length;
        n_trial++;

        //@V2 Show the game header
        game_header(n_trial, m_trial, level);

        //2b. padding top
        cout<<"\n\n\n";

        //2a. Draw the Rectangle
        for(int i=0;i<length;i++){
            //2b. Padding left
            cout << "\t\t";
            for(int j=0; j<width; j++){
                cout<<"# ";
            }
            cout<<"\n";
        }

        //3c. Set Start time
        user_stime = time(0);
        //3a. Ask User
        cout<<"Area = ";
        cin >>user_area;
        //3c. Set end time and calc diff
        user_timeout = time(0) - user_stime;
        cout<<"You take " << user_timeout <<"s to answer!....\n";

        //4a. Compare Answer and Give them point
        if(user_area==area && user_timeout <= g_timeout){
            score++;
            cout<< "\tCorrect :)\n";
        }else if(user_area!= area){
            cout<< "\tWrong :( \n";
        }else {
            cout<< "\tTimeout :|, try fast\n";
        }

        //4b. Clear Screen
        //@V2 Clear Screen and ReShow header
        game_header(n_trial, m_trial, level);
        //@V2 Wait before replay
        start_after(3);
    }
    //5a. Check the number of trial
    while(n_trial<m_trial);

    //6a. Game over and print socre
    cout<<"\n\t\tGAME OVER\n";
    cout<<"\n\t\tYour Score is :" <<(score*1.0/m_trial)*100.0 <<"%\n";

    return 0;
}
