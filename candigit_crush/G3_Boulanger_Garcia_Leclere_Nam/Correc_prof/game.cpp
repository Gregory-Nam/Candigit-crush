#include <iostream>

#include "game.h"
#include "Correc_prof/params.h"
#include "Correc_prof/gridmanagement.h"

using namespace std;
void Menu (CPosition & Pos, char & Direction)
{
    cout << "Saisir un indice de ligne, un indice de column,\n"
            " et un sens de Deplacements : \n"
                                         "a a gauche,\n "
                                         "s en bas,\n"
                                         "e a droite,\n "
                                         "z en haut\n"
         << endl;
    cin >> Pos.first >> Pos.second >> Direction;

} // Menu()

void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction)
{
    unsigned NewLineNumber (Pos.first), NewColumnNumber (Pos.second);
    switch (Direction) {
        case 'a':
            --NewColumnNumber;
            break;
        case 's':
            ++NewLineNumber;
            break;
        case 'e':
            ++NewColumnNumber;
            break;
        case 'z':
            --NewLineNumber;
            break;
        default :
            exit (EXIT_FAILURE);
    }
    swap (Grid [Pos.first][Pos.second], Grid [NewLineNumber][NewColumnNumber]);
} // MakeAMove ()

bool AtLeastThreeInARow (const CMat & Mat, CPosition & Pos, unsigned & HowMany)
{
    for (unsigned LineNumber = 0; LineNumber < Mat.size (); ++LineNumber)
    {
        for (unsigned ColNmber = 0; ColNmber < Mat.size () -2; ++ColNmber)
        {
            if (KImpossible == Mat[LineNumber][ColNmber]) continue;
            for (HowMany = 1; ColNmber + HowMany < Mat.size() && Mat [LineNumber][ColNmber] == Mat[LineNumber][ColNmber + HowMany]; ++HowMany);
            if (HowMany > 2)
            {
                Pos = make_pair (LineNumber, ColNmber);
                return true;
            }
        }
    }
    return false;
} // AtLeastThreeInARow ()

bool AtLeastThreeInAColumn (const CMat & Mat, CPosition & Pos, unsigned & HowMany)
{
    for (unsigned ColNmber = 0; ColNmber < Mat.size (); ++ColNmber)
    {
        for (unsigned LineNumber = 0; LineNumber < Mat.size () -2; ++LineNumber)
        {
            if (KImpossible == Mat[LineNumber][ColNmber]) continue;
            for (HowMany = 1; LineNumber + HowMany < Mat.size() && Mat [LineNumber][ColNmber] == Mat[LineNumber + HowMany][ColNmber]; ++HowMany);

            if (HowMany > 2)
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
    for (; Pos.first + Nb + HowMany < Mat.size (); ++Nb)
    {
        Mat [Pos.first + Nb][Pos.second] = Mat [Pos.first + Nb + HowMany][Pos.second];
        Mat [Pos.first + Nb + HowMany][Pos.second] = KImpossible;
    }
    for (; Pos.first + Nb < Mat.size (); ++Nb)
        Mat [Pos.first + Nb][Pos.second] = KImpossible;
} // ReplaceColumn()

void RemovalInRow (CMat & Mat, const CPosition & Pos, const unsigned & HowMany)
{
    CPosition PosToRemove (Pos);
    for (unsigned i (0); i < HowMany; ++i)
    {
        RemovalInColumn (Mat, PosToRemove, 1);
        ++PosToRemove.second;
    }
} // ReplaceRow ()

unsigned ComputeScore (unsigned Score)
{
    return Score * (Score + 1) / 2;
}

int ppal ()
{
    srand (time (NULL));
    cout << "Welcome to number crush!" << endl;
    CMat Grid;
    InitGrid (Grid, 10);
    CPosition Pos;
    unsigned HowMany, Score (0);
    char Dirrection;

    for (unsigned Count (0); Count < KMaxTimes; ++Count)
    {
        DisplayGrid (Grid);
        Menu (Pos, Dirrection);
        if ('q' == Dirrection) break;
        MakeAMove (Grid, Pos, Dirrection);

        while (AtLeastThreeInAColumn (Grid, Pos, HowMany))
        {
            RemovalInColumn (Grid, Pos, HowMany);
            Score += ComputeScore (HowMany);
        }
        while (AtLeastThreeInARow (Grid, Pos, HowMany))
        {
            RemovalInRow (Grid, Pos, HowMany);
            Score += ComputeScore (HowMany);
        }
    }
    cout << "Your score is : " << Score << endl << "That's not so bad for a dummy ;)" << endl;
    return 0;
}
