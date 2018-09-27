#ifndef GAME_H
#define GAME_H

#include "Correc_prof/type.h"

void Menu (CPosition & Pos, char & Direction);

void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction);

bool AtLeastThreeInARow (const CMat & Mat, CPosition & Pos, unsigned & HowMany);

bool AtLeastThreeInAColumn (const CMat & Mat, CPosition & Pos, unsigned & HowMany);

void RemovalInColumn (CMat & Mat, const CPosition & Pos, const unsigned & HowMany);

void RemovalInRow (CMat & Mat, const CPosition & Pos, const unsigned & HowMany);

unsigned ComputeScore (unsigned Score);

int ppal ();
#endif // GAME_H

