#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <algorithm>

#include "timer.h"
#include <mutex>

using namespace std;

mutex g_mutex;

char g_title_start[] = {0x1b, ']', '0', ';', 0};
char g_title_end[] = {0x07, 0};

#define STARTTITLE g_title_start
#define ENDTITLE g_title_end

//--------------------------------
struct timer_data
{
    time_t nStartTime;
    time_t nLastTime;
    int nTotalScore;
    bool bPartieFinie;
    int nGameTime = 60;
    char chKeyUp = 'z';
    char chKeyDown = 's';
    char chKeyLeft = 'q';
    char chKeyRight = 'd';
    unsigned nLifeCpt = 5;
} g_data;
//-- Conteneur des données principales ----------------


void TimerThread()
{
start:
    while (true)
    {
        lock_guard<mutex> lock(g_mutex);

        g_data.nLastTime = time(NULL);
        char t[6];
        int seconds, minutes;
        seconds = g_data.nLastTime-g_data.nStartTime;


        int remaining = g_data.nGameTime-seconds;
        minutes = remaining/60;

        int _minutes = minutes%60;
        int _seconds = remaining%60;

        char format_minutes[3];
        char format_seconds[3];

        //sprintf: fonction standard du C qui formatte un tableau de caractères
        sprintf(format_minutes, _minutes < 10 ? "0%d" : "%d", _minutes); // Préfixe un 0 si le nombre des minutes ne compte qu'un caractère
        sprintf(format_seconds, _seconds < 10 ? "0%d" : "%d", _seconds); // Préfixe un 0 si le nombre des secondes ne compte qu'un caractère

        sprintf(t, "%s:%s", format_minutes, format_seconds);



        if ( remaining > 0 )
        {
             cout << STARTTITLE << "[  Vies  :  " << g_data.nLifeCpt << " ]  |  " << "[ Score actuel  :   " << g_data.nTotalScore << " ]   |   " << t << ENDTITLE <<
                     flush;
        }
        else if ( remaining <= 0 )
        {
            cout << STARTTITLE  <<  "[  Vies  :  " << g_data.nLifeCpt << " ]  |  " << "[ Score final  :   " << g_data.nTotalScore << " ]  |   " << "00:00   Partie terminée" << ENDTITLE << flush;
            g_data.bPartieFinie = true;
            break;
        }
    }

    while ( g_data.bPartieFinie );

    goto start;
}
