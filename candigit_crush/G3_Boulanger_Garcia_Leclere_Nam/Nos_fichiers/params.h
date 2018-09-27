#ifndef PARAMS_H
#define PARAMS_H

#include <string>

/**
 * @file params.h
 */

/**
 * @brief KNbCandies : Constante du chiffre maximal
 */

const unsigned KNbCandies  = 4;

/**
 * @brief KImpossible : Constante qui nous permet de representer une case vide
 */
const unsigned KImpossible = KNbCandies + 2;

/**
 * @brief KReset : constante couleur
*/
const std::string KReset   ("0");
/**
 * @brief KBlack : constante couleur
 */
const std::string KBlack   ("30");
/**
 * @brief KRed : constante couleur
 */
const std::string KRed     ("31");
/**
 * @brief KGreen : constante couleur
 */
const std::string KGreen   ("32");
/**
 * @brief KJYellow : constante couleur
 */
const std::string KJYellow ("33");
/**
 * @brief KBlue : constante couleur
 */
const std::string KBlue    ("34");
/**
 * @brief KMAgenta : constante couleur
 */
const std::string KMAgenta ("35");
/**
 * @brief KCyan : constante couleur
 */
const std::string KCyan    ("36");
/**
 * @brief KGray : constante couleur
 */
const std::string KGray    ("37");
/**
 * @brief KBackground : constante couleur
 */
const std::string KBackground("40");

#endif // PARAMS_H
