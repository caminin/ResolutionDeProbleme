#ifndef CHRONO
#define CHRONO

#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>

/**
 * \file Chrono.hpp
 * \brief interface pour la class chrono en c++
 * \author CHARLOT Rodolphe
 * \version 1.0
 * \date 24 janvier 2016
 * \licence BSD
 *
 * Class destinée à simpifier l'utilisation de la class chrono dans std 
 * Elle permet notamment une pause et reset, et une précision variable
 * Elle peut être réutilisée sous les conditions de sa licence
 *
 */



class Chrono
{
public:
  /**
  *   \brief Constructeur
  *   \param elapsed_time Temps avec lequel le chrono démarre, 0 par défaut
  *   \param precision Unités du chrono, milliseconds par défaut
  */
  Chrono( float elapsed_time=0,std::string precision="milliseconds");
  /**
  *   \brief Lance le chrono
  *
  *   Mets la valeur du temps actuel dans _start et isCalculing à true
  */
  void start();
  /**
  *   \brief Arréte le chrono 
  *   
  *   Prend la valeur de _start et la compare avec la valeur de temps actuel, ajoute le résultat dans _elapsed_time
  */
  void stop();
  /**
  *   \brief Remets le chrono a zéro
  *
  *   Mets la valeur de elapsed_time à 0
  */
  void reset();
  /**
  *   \brief Renvoie la valeur de elapsed_time
  *
  *   Permet aux méthodes qui utilisent le chrono de récupérer la valeur finale
  */
  float getDuration();
  
  std::string getTime();
  
  std::string getPrecision(){return _precision;}
private:
  /** Temps de départ du chrono*/
  std::chrono::time_point<std::chrono::system_clock> _start;
  /** Temps entre un start() et un stop() */
  float _elapsed_time;
  /** unité du temps du test */
  std::string _precision;
  /** booléen si le chrono a démarré ou pas*/
  bool _isCalculing;
};


#endif // __TESTENV_INCLUDED__


