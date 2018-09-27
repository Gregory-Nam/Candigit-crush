#include <iostream>
#include "G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/timer.h"
#include "G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/game.h"
#include "G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/type.h"

#include <thread>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

map<string, string> config;

int main()
{
    try
    {
        g_data.nStartTime = time(NULL);
        g_data.nTotalScore = 0;

        ifstream ifs("../G3_Boulanger_Garcia_Leclere_Nam/Nos_fichiers/config.cfg");
        if ( ifs.is_open() )
        {
            cout << "Fichier de configuration ouvert" << endl;
            string str;
            while ( getline(ifs, str) )
            {
                stringstream ss(str);
                string key;
                string val;
                ss >> key;
                ss >> val;

                if ( !key.empty() && !val.empty() )
                {
                    config[key] = val;
                }
            }
        }
        else
            cout << "Impossible d'ouvrir le fichier de configuration" << endl;

        for (map<string, string>::iterator it = config.begin(); it != config.end(); it++)
        {
            if ( it->first == "settimelimit" )
                g_data.nGameTime = atoi(it->second.c_str());
            else if ( it->first == "setkeyup" )
                g_data.chKeyUp = it->second[0];
            else if ( it->first == "setkeydown" )
                g_data.chKeyDown = it->second[0];
            else if ( it->first == "setkeyleft" )
                g_data.chKeyLeft = it->second[0];
            else if ( it->first == "setkeyright" )
                g_data.chKeyRight = it->second[0];
            else
                cout << "Paramètre de configuration inconnu : '" << it->first << endl;
        }

        thread th1( TimerThread ); //procédure asynchrone de gestion du temps de jeu
        cout << "Temps de partie de " << g_data.nGameTime << " secondes" << endl;
        cout << g_data.chKeyUp << " : vers le haut" << endl;
        cout << g_data.chKeyDown << " : vers le bas" << endl;
        cout << g_data.chKeyLeft << " : vers la gauche" << endl;
        cout << g_data.chKeyRight << " : vers la droite" << endl;

        ppal();


        th1.join();

    }
    catch ( exception & ex )
    {
        cout << "Erreur quelque part (" << ex.what() << ")" << endl;
        exit( EXIT_FAILURE );
    }

    return 0;

}

