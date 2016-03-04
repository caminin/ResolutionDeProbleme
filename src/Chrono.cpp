#include "../include/Chrono.hpp"

/**
 * \file Chrono.cpp
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


using namespace std;

Chrono::Chrono(float elapsed_time,string newPrecision):_elapsed_time(elapsed_time),_precision(newPrecision),_isCalculing(false)
{}


void
Chrono::start()
{
    _isCalculing=true;
    _start = chrono::system_clock::now();

}

void
Chrono::stop()
{
    if(_isCalculing==true)
    {
        chrono::time_point<chrono::system_clock> end=chrono::system_clock::now();
        _isCalculing=false;
        if(_precision=="nanoseconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::nanoseconds>(end-_start).count();
        }
        else if(_precision=="microseconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::microseconds>(end-_start).count();
        }
        else if(_precision=="milliseconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::milliseconds>(end-_start).count();
        }
        
        else if(_precision=="seconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::seconds>(end-_start).count();
        }
        else
        {
            _elapsed_time+=chrono::duration_cast<chrono::milliseconds>(end-_start).count();
        }
                                 
    }
    else
        cerr << "Le chrono n'a pas démarré, vous ne pouvez pas le stopper" << endl;
}
void
Chrono::reset()
{
    _elapsed_time=0;
}
float
Chrono::getDuration()
{
    return _elapsed_time;
}

string
Chrono::getTime()
{
    string s=to_string(_elapsed_time)+" "+_precision;
    return s;
}

