#include <iostream>     // cout, cin
#include <stdlib.h>     // rand, system
#include <unistd.h>     // sleep
#include <windows.h>
#include <ctime>        // time.now

using namespace std;

int main()
{
    //0a. Define Variable
    int m_trial = 5;
    int n_trial = 0;
    int score = 0;
    int width, length ;
    long area , userAnswer;

    //0b. Print Game instructions
    cout << "\t\t***Welcome to my first Game :)****\n";
    cout << "\tVision the Shape and Calculate its Area in 5 seconds. \n";
    cout << "\n\nPress Any key to start";

    //0c. Change random based on time
    time_t user_time, user_clock;
    int g_timeout = 5;
    srand(time(0));

    cin.get();

    do{
        //1a. Initiate Variables
        width = 2+rand()%5;
        length = 2+rand()%5;
        area = width * length;
        userAnswer;
        n_trial++;

        //2b. padding top
        cout<<"\n\n\n";
        //2a. Draw the Rectangle
        for(int i=0;i<length;i++){
            //2b. Padding
            cout << "\t\t";
            for(int j=0; j<width; j++){
                cout<<"#";
            }
            cout<<endl;
        }
        //3c. Set time
        user_clock = time(0);
        //3a. Ask User
        cout<<"Area = ";
        cin >>userAnswer;
        user_time = time(0) - user_clock;
        cout<<"You take " << user_time <<"s to answer!....\n";

        //4a. Compare Answer and Give them point
        if(userAnswer==area && user_time <= g_timeout){
            score++;
            cout<< "\tCorrect :)\n";
        }else if(userAnswer!= area){
            cout<< "\tWrong :( \n";
        }else {
            cout<< "\tTimeout :|, try fast\n";
        }

        //4b. Clear Screen
        sleep(2);
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
    cout<<"GAME OVER\n";
    cout<<"Your Score is :" <<(score*1.0/m_trial)*100.0 <<"%\n";

    return 0;
}
