#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

/**
  * @file gridmanagement.h
  */

#include <string>

#include "G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/type.h" //nos types
#include "G3_Boulanger_Garcia_Leclere_Nam/Correc_prof/nsutil.h"

/**
 * @brief Efface le contenu actuel du terminal
 */
void ClearScreen ();

/**
 * @brief Active le mode couleur dans le terminal
 * @param Col : Code couleur
 */
void Color (const std::string & Col);

/**
 * @brief Affiche la grille en prenant en compte la couelur
 * @param Mat : La grille actuelle
 */
void DisplayGridWithLineAndColumnNumbersAndColor (const CMat & Mat);

/**
 * @brief Affiche la grille sans prendre en compte la couleur
 * @param Mat : La grille actuelle
 */
void DisplayGridWithLineAndColumnNumbers (const CMat & Mat);

/**
 * @brief Affiche la grille
 * @param Mat : La grille actuelle
 * @param ShowLineNumber : Affiche ou non les numéros de ligne
 * @param ShowColor : Afficher ou non la couleur
 */
void DisplayGrid (const CMat & Mat, bool ShowLineNumber = true, bool ShowColor = true);


/**
 * @brief Initialise les éléments de la grille
 * @param Grid : La grille à initialiser
 * @param Size : Taille de la grille souhaitée
 */
void InitGrid (CMat & Grid, unsigned Size);

#endif // GRIDMANAGEMENT_H
