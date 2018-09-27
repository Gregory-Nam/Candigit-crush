#include <iostream>
#include <iomanip>
#include "gridmanagement.h"

#include "type.h" //nos types
#include "params.h" //nos parametres

using namespace std;
#include <mutex>
extern mutex g_mutex;


void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()

void DisplayGridWithLineAndColumnNumbersAndColor (const CMat & Mat)
{
    ClearScreen ();
    Color(KBackground);
    string Rule (4*Mat.size () + 1, '=');
    cout << string (3, ' ');
    Color(KRed);
    cout << setw(2) << Rule;
    cout << endl;
    cout << string (4, ' ');
    for ( unsigned i (0); i < Mat.size (); ++i )
    {
        Color (KBlue);
        cout << setw (2) << i;
        Color (KRed);
        cout<< setw (2) << '|';
    }
    cout << endl;
    Rule = string (3, ' ') + Rule;
    Color (KRed);
    cout << Rule << endl;
    unsigned LineNumber (0);
    for ( const CVLine & Aline : Mat )
    {
        Color (KBlue);
        cout << setw (2) << LineNumber++;
        Color (KRed);
        cout << "||";
        for ( auto Cel : Aline )
        {
            Color (KBlack);
            cout << setw (2);
            if ( KImpossible == Cel )
                cout << ' ';
            else if ( Cel == 1 )
            {
                Color(KCyan);
                cout << ' ' << Cel;
            }
            else if ( Cel == 2 )
            {
                Color(KGray);
                cout << ' ' << Cel;
            }
            else if ( Cel == 3 )
            {
                Color(KJYellow);

                cout << ' ' << Cel;
            }
            else if ( Cel == 4 )
            {
                Color(KMAgenta);
                cout << ' ' << Cel;
            }
            else
                cout << Cel;
            Color (KRed);
            cout<< setw (2) << '|';
        }
        Color (KRed);
        cout << endl << Rule << endl;
    }
    Color (KReset);
} // DisplayWithLineAndColumnNumbersAndColor ()
void DisplayGridWithLineAndColumnNumbers (const CMat & Mat)
{
    ClearScreen ();
    cout << string (4, ' ');
    for ( unsigned i (0); i < Mat.size (); ++i )
        cout << setw (2) << i << setw (2) << '|';
    cout << endl;
    string Rule (4*Mat.size () + 1, '=');
    Rule = string (3, ' ') + Rule;
    cout << Rule << endl;
    unsigned LineNumber (0);
    for ( const CVLine & Aline : Mat )
    {
        cout << setw (2) << LineNumber++ << '|';
        cout << '|';
        for ( auto Cel : Aline )
            cout << setw (2) << Cel << setw (2) << '|';
        cout << endl << Rule << endl;
    }
} // DisplayWithLineAndColumnNumbers ()


void DisplayGrid (const CMat & Mat, bool ShowLineNumber /*= true*/, bool ShowColor /*= true*/)
{
    lock_guard<mutex> lock(g_mutex);
    ClearScreen ();
    if ( ShowLineNumber )
    {
        if ( ShowColor )
            DisplayGridWithLineAndColumnNumbersAndColor (Mat);
        else
            DisplayGridWithLineAndColumnNumbers (Mat);
        return;
    }

    string Rule (4*Mat.size () + 1, '=');
    cout << Rule << endl;
    for ( const CVLine & Aline : Mat )
    {
        cout << '|';
        for ( auto Cel : Aline )
            cout << setw (2) << Cel << setw (2) << '|';
        cout << endl << Rule << endl;
    }
}// DisplayGrid ()


void InitGrid (CMat & Grid, unsigned Size)
{
    Grid.resize (Size);
    for ( auto & Line : Grid )
    {
        Line.resize (Size);
        for ( auto & Cel : Line )
            Cel = Rand () +1;
     }
} // InitMat ()

