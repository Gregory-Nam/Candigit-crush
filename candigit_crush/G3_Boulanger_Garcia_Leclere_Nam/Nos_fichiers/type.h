//conteneur des données principales, défini dans main.cpp
/**
  * @file type.h
  */


/**
 * @struct timer_data
 * @brief Conteneur des données du jeu.
 *
 * nStartTime   :   Temps au début de la partie
 * nLastTime    :   Dernier temps enregistré
 * nTotalScore  :   Score global
 * PartieFini   :   Déclencheur de fin de partie
 */
extern struct timer_data
{
    /**
     * @brief nStartTime Temps de début de partie
     */
    time_t nStartTime;
    /**
     * @brief nLastTime Temps de fin de partie
     */
    time_t nLastTime;
    /**
     * @brief nTotalScore Score total;
     */
    int nTotalScore;
    /**
     * @brief PartieFini Déclancheur fin de partie
     */
    bool bPartieFinie; /* = false;*/

    /**
     * @brief nGameTime Temps de la partie
     */
    int nGameTime;

    /**
     * @brief chKeyUp Touche directionnelle haut
     */
    char chKeyUp;

    /**
     * @brief chKeyDown Touche directionnelle bas
     */
    char chKeyDown;

    /**
     * @brief chKeyLeft Touche directionnelle gauche
     */
    char chKeyLeft;

    /**
     * @brief chKeyRight Touche directionnelle droite
     */
    char chKeyRight;

    /**
     * @brief nLifeCpt Compteur de vies
     */
    unsigned nLifeCpt;

} g_data;

