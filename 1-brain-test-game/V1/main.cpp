#include <iostream>     // cout, cin
#include <stdlib.h>     // rand, srand, system
#include <unistd.h>     // sleep
#include <time.h>       // time.now time_t

using namespace std;

//0a. Define Variable
int level_width;
int level_length;
int user_level;

int m_trial, n_trial;
int score, g_timeout;
int width, length;
int area , user_area;
int table_size;
time_t user_stime, user_timeout;

int play_again_selection;


void select_level() {

    cout << "\nChoose Level :\n \t\t 1 to Easy - 2 to Medium - 3 to Hard : ";
    cin >> user_level;
    if (user_level == 1) {
        level_width = level_length = 2;
        table_size  = 3;
    } else if (user_level == 2) {
        level_width = level_length = 4;
        table_size  = 4;
    } else if (user_level == 3) {
        level_width = level_length = 6;
        table_size  = 5;
    } else {
        cout << "Please Enter Valid Number . \n";
        select_level();
    }


}


int main()
{
    //1a. Initiate Variables
    g_timeout   = 5;
    table_size  = 5;
    m_trial     = 5;
    n_trial     = 0;
    score       = 0;
    //0c. Change random based on time
    srand(time(0));

    //0b. Print Game instructions
    cout << "\t\t***Welcome to my first Game :)****\n";
    cout << "\tVision the Shape and Calculate its Area in "<<g_timeout<<" seconds. \n";
    select_level();

    do{
        //------Initiate Variables repeated part
        width       = 2+rand()%table_size;
        length      = 2+rand()%table_size;
        area        = width * length;
        n_trial++;

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
        sleep(3);
        system("cls");
        for(int i=3; i>0; i--){
            cout<< "\n\t\tStart Next in "<< i << "s...\n";
            sleep(1);
            system("cls");
        }

    }
    //5a. Check the number of trial
    while(n_trial<m_trial);

    //6a. Game over and print socre
    cout<<"\t\tGAME OVER\n";
    cout<<"\t\tYour Score is :" <<(score*1.0/m_trial)*100.0 <<"%\n";

    return 0;
}
