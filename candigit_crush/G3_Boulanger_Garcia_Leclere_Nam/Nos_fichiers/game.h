#ifndef GAME_H
#define GAME_H

/**
  * @file game.h
  */

#include "G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/type.h"

/**
 * @brief Affiche les touches d'interactions disponibles et attend l'entrée de l'utilisateur
 * @param Pos : Position actuelle
 * @param Direction : Direction du déplacement
 */
void Menu (CPosition & Pos, char & Direction);

/**
 * @brief Procède au mouvement
 * @param Grid : Grille actuelle
 * @param Pos : Position actuelle dans la grille
 * @param Direction : Direction du mouvement
 */
void MakeAMove (CMat & Grid, const CPosition & Pos, char Direction);

/**
 * @brief Calcule si une suite d'au moins 3 nombres en ligne est présente à la position actuelle
 * @param Mat : Grille actuelle
 * @param Pos : Position actuelle dans la grille
 * @param HowMany : Correspond au nombre de combinaison trouvé dans la matrice
 * @return vrai si HowMany est supérieur ou égal à 3
 */
bool AtLeastThreeInARow (const CMat & Mat, CPosition & Pos, unsigned & HowMany);

/**
 * @brief Calcule si une suite d'au moins 3 nombres en colonne est présente à la position actuelle
 * @param Mat : Grille actuelle
 * @param Pos : Position actuelle dans la grille
 * @param HowMany : Retourne le nombre de combos trouvés dans cette variable
 * @return vrai si HowMany est supérieur ou égal à 3
 */
bool AtLeastThreeInAColumn (const CMat & Mat, CPosition & Pos, unsigned & HowMany);

/**
 * @brief Supprime des éléments dans la colonne actuelle
 * @param Mat : Grille actuelle
 * @param Pos : Position actuelle
 * @param HowMany : Le nombre d'éléments à retirer
 */
void RemovalInColumn (CMat & Mat, const CPosition & Pos, const unsigned & HowMany);

/**
 * @brief Supprime est éléments dans la ligne actuelle
 * @param Mat : Grille actuelle
 * @param Pos : Position actuelle
 * @param HowMany : Le nombre d'éléments à retirer
 */
void RemovalInRow (CMat & Mat, const CPosition & Pos, const unsigned & HowMany);

/**
 * @brief Calcule le nouveau score
 * @param Score : score actuel
 */
unsigned ComputeScore (unsigned Score);


/**
 * @brief Fonction principale du jeu
 * @return
 */

int ppal ();

/**
 * @brief LifeCounter : Verifie si un mouvement à été efficace.
 * @param LifeCpt : Nombre de vie.
 * @param InColumn : Verifie le mouvement sur la colonne.
 * @param InRow : Verifie le mouvement sur la ligne;
 */
unsigned LifeCounter(unsigned & LifeCpt,bool InColumn , bool InRow);


#endif // GAME_H
