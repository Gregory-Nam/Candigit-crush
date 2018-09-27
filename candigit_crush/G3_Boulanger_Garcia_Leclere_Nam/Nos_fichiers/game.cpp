#include <iostream>
#include <mutex>
#include <fstream>
#include <istream>
#include "game.h"
#include <time.h>
#include "params.h"
#include "gridmanagement.h"
#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;
extern mutex g_mutex;



unsigned LifeCounter( unsigned & LifeCpt,bool InColumn , bool InRow )
{
    if ( !InColumn && !InRow )
        --LifeCpt;
    return LifeCpt;
}


void Menu ( CPosition & Pos, char & Direction )
{
    if ( g_data.bPartieFinie )
        return;

    bool EntreeValide = false;
    cout << "Veuillez saisir une ligne : ";
    while ( !EntreeValide )
    {
        cin >> Pos.first;
        cout << endl;

        string str = std::to_string(Pos.first);

        if ( cin.fail() || str.size() > 1 )
        {
            cout << "Veuillez rentrez un indice de ligne valide : ";
            cin.clear();
            cin.ignore( 10,'\n' );
            cout << endl;
        }
        else
        {
            EntreeValide = true;
        }
    }
    EntreeValide = false;

    cout << "Veuillez saisir une colonne : ";
    while ( !EntreeValide )
    {
        cin >> Pos.second;
        cout << endl;
        if ( cin.fail() || Pos.second > 9 )
        {
            cout << "Veuillez rentrez un indice de colonne valide : ";
            cin.clear();
            cin.ignore( 1000, '\n' );
        }
        else
        {
            EntreeValide = true;
        }
    }
    string Direct;
    unsigned k = 0;
    cout << "Veuillez saisir une direction : ";
    while ( true )
    {
        getline( cin, Direct );
        if ( Direct.size() == 1 && ( Direct[0] == g_data.chKeyUp || Direct[0] == g_data.chKeyDown ||Direct[0] == g_data.chKeyLeft ||Direct[0] == g_data.chKeyRight ))
        {
            Direction = tolower( Direct[0] );

            break;
        }
        else
        {
            if ( k > 0)
                cout << "Veuillez rentrer une direction valide : ";
            ++k;
            continue;
        }
    }
} // Menu()



unsigned BonusRow( const CMat & Grid )
{
    unsigned emptyrows = 0;
    for ( const CVLine & Line : Grid )
    {
        unsigned cpt = 0;
        for ( const unsigned & Val : Line )
        {
            if ( Val == KImpossible )
                ++cpt;

            if (cpt == Grid.size())
                emptyrows++;
        }
    }
    return emptyrows;
} //BonusRow

unsigned BonusCol(const CMat & Grid)
{
    int emptycols = 0;
        for ( unsigned i = 0; i < Grid.size(); ++i )
        {

            unsigned j = 0;
            bool empty = false;
            if ( Grid[j][i] != KImpossible ) continue;
            else
            {
                while ( Grid[j][i] == KImpossible && j < Grid.size() )
                {
                    ++j;
                    if ( j == Grid.size() )
                    {
                        empty = true;
                        break;
                    }
                }
            }

            if (empty)
                emptycols++;
        }

        return emptycols;
} //BonusCol

void MakeAMove (CMat & Grid, CPosition & Pos, char Direction)
{
    unsigned NewLineNumber ( Pos.first ), NewColumnNumber ( Pos.second );

    if ( Direction == g_data.chKeyLeft )
    {
        if ( Pos.second == 0 )
        {
            NewColumnNumber = Grid.size()-1;
            while ( Grid[Pos.first][NewColumnNumber] == KImpossible )
                --NewColumnNumber;
        }
        else if ( Grid[Pos.first][Pos.second - 1] == KImpossible )
        {
            bool Find = false;
            for ( unsigned i = Pos.second-1; i > 0; --i )
                if ( Grid[Pos.first][i] != KImpossible ) Find = true;
            if ( !Find )
            {
                NewColumnNumber = Grid.size()-1;
                while ( Grid[Pos.first][NewColumnNumber] == KImpossible )
                    --NewColumnNumber;
            }
        }
        else if ( Grid[Pos.first][Pos.second] != KImpossible )
            --NewColumnNumber;
    }
    else if ( Direction == g_data.chKeyDown )
    {
        if ( Pos.first == Grid.size()-1 || Grid[Pos.first + 1][Pos.second] == KImpossible )
        {
            NewLineNumber = 0;
            while ( Grid[Pos.first - 1][Pos.second] == KImpossible )
                ++NewLineNumber;
        }
        else
            ++NewLineNumber;
    }
    else if ( Direction == g_data.chKeyRight )
    {
        if ( Pos.second == Grid.size()-1 )
        {
            NewColumnNumber = 0;
            while ( Grid[Pos.first][NewColumnNumber] == KImpossible )
                ++NewColumnNumber;
        }
        else if ( Grid[Pos.first][Pos.second + 1] == KImpossible )
        {
            bool Find = false;
            for ( unsigned i = Pos.second+1; i < Grid.size(); ++i )
                if ( Grid[Pos.first][i] != KImpossible ) Find = true;
            if ( !Find )
            {
                NewColumnNumber = 0;
                while ( Grid[Pos.first][NewColumnNumber] == KImpossible )
                    ++NewColumnNumber;
            }
        }
        else
            ++NewColumnNumber;
    }
    else if ( Direction == g_data.chKeyUp )
    {
        if ( Pos.first == 0 )
        {
            NewLineNumber = Grid.size()-1;
            while ( Grid[NewLineNumber][Pos.second] == KImpossible )
                --NewLineNumber;
        }
        else
            --NewLineNumber;
    }
    else
        goto skip;

    swap ( Grid [Pos.first][Pos.second], Grid [NewLineNumber][NewColumnNumber] );

skip:
    return;

} // MakeAMove ()

bool AtLeastThreeInARow ( const CMat & Mat, CPosition & Pos, unsigned & HowMany )
{
    for ( unsigned LineNumber = 0; LineNumber < Mat.size (); ++LineNumber )
    {
        for ( unsigned ColNmber = 0; ColNmber < Mat.size () -2; ++ColNmber )
        {
            if ( KImpossible == Mat[LineNumber][ColNmber] ) continue;
            for ( HowMany = 1; ColNmber + HowMany < Mat.size() && Mat [LineNumber][ColNmber] == Mat[LineNumber][ColNmber + HowMany]; ++HowMany );
            if ( HowMany > 2 )
            {
                Pos = make_pair ( LineNumber, ColNmber );
                return true;
            }
        }
    }
    return false;
} // AtLeastThreeInARow ()


bool AtLeastThreeInAColumn (const CMat & Mat, CPosition & Pos, unsigned & HowMany)
{
    for ( unsigned ColNmber = 0; ColNmber < Mat.size (); ++ColNmber )
    {
        for ( unsigned LineNumber = 0; LineNumber < Mat.size () -2; ++LineNumber )
        {
            if ( KImpossible == Mat[LineNumber][ColNmber] ) continue;
            for ( HowMany = 1; LineNumber + HowMany < Mat.size() && Mat [LineNumber][ColNmber] == Mat[LineNumber + HowMany][ColNmber]; ++HowMany );
            if ( HowMany > 2 )
            {
                Pos = make_pair (LineNumber, ColNmber);
                return true;
            }
        }
    }
    return false;

} // AtLeastThreeInAColumn ()


void RemovalInColumn (CMat & Mat, const CPosition & Pos, const unsigned & HowMany)
{
    unsigned Nb (0);
    for ( ; Pos.first + Nb + HowMany < Mat.size (); ++Nb )
    {
        Mat [Pos.first + Nb][Pos.second] = Mat [Pos.first + Nb + HowMany][Pos.second];
        Mat [Pos.first + Nb + HowMany][Pos.second] = KImpossible;
    }
    for ( ; Pos.first + Nb < Mat.size (); ++Nb )
        Mat [Pos.first + Nb][Pos.second] = KImpossible;
} // ReplaceColumn()


void RemovalInRow (CMat & Mat, const CPosition & Pos, const unsigned & HowMany)
{
    CPosition PosToRemove (Pos);
    for ( unsigned i (0); i < HowMany; ++i )
    {
        RemovalInColumn ( Mat, PosToRemove, 1 );
        ++PosToRemove.second;
    }
} // ReplaceRow ()


unsigned ComputeScore (unsigned HowMany, unsigned Score)
{
    if ( HowMany == 4 )
    {
        return  ( Score * HowMany)+ ((1/2) * (Score * HowMany ));
    }
    else if ( HowMany == 5 )
    {
        return 2 * ( Score * HowMany );
    }
    else if ( HowMany > 5 )
    {
        return 5 * ( Score * HowMany );
    }

    return Score * HowMany;
} //ComputeScore

int ppal ()
{
 gameloop:
    srand (time (NULL));
    cout << "Welcome to Candigit Crush!" << endl;
    CMat Grid;
    InitGrid (Grid, 10);
    CPosition Pos;
    unsigned HowMany;
    char Direction;
    unsigned EmptyLine = 0;
    unsigned EmptyCol = 0;

    while ( !g_data.bPartieFinie && g_data.nLifeCpt != 0 )
    {
        LifeCounter(g_data.nLifeCpt, AtLeastThreeInAColumn (Grid, Pos, HowMany), AtLeastThreeInARow (Grid, Pos, HowMany));
        while ( AtLeastThreeInAColumn (Grid, Pos, HowMany ))
        {
            g_data.nTotalScore += ComputeScore (HowMany,Grid[Pos.first][Pos.second]);
            RemovalInColumn (Grid, Pos, HowMany);

        }
        while ( AtLeastThreeInARow (Grid, Pos, HowMany ))
        {
            g_data.nTotalScore += ComputeScore (HowMany,Grid[Pos.first][Pos.second]);
            RemovalInRow (Grid, Pos, HowMany);

        }
        DisplayGrid (Grid);
        unsigned BonRow = BonusRow(Grid);
        unsigned BonCol = BonusCol(Grid);

        if ( BonRow > EmptyLine )
        {
            g_data.nTotalScore += (BonRow - EmptyLine) * 10;
            ++EmptyLine;
        }

        if ( BonCol > EmptyCol )
        {
            g_data.nTotalScore += (BonCol - EmptyCol) * 20;
            ++EmptyCol;
        }

        Menu (Pos, Direction);

        if ( 'q' == Direction ) break;

        MakeAMove (Grid, Pos, Direction);
    }

    if( !g_data.nLifeCpt )
    {
        cout << "Vous n'avez plus de vie ! Appuyer sur R pour recommencer ou n'importe quelle autre touche pour quitter" << endl << flush;
    }
    else
    {
        cout << "Le temps est écoulé ! Votre dernier coup est refusé !" << endl << "Appuyer sur R pour recommencer ou n'importe quelle autre touche pour quitter."<< endl << flush;
    }

    g_data.bPartieFinie = true;
    char r;
    cin >> r;
    if ( toupper(r) == 'R' )
    {
        g_data.bPartieFinie = false;
        g_data.nStartTime = time(NULL);
        g_data.nTotalScore = 0;
        g_data.nLifeCpt = 5;
        goto gameloop;
    }

    exit(0);

} //ppal

