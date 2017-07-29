#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>

using namespace std ;

class LSystem
{
    string alphabet ;

    string axiom ;

    string tree ;

    string *rules ;

    int step ;


public:

    LSystem();

    ~LSystem() ;

    LSystem(const string &ax , const string &al = "[]+-FAB") ;

    string& operator() (int i) ;

    string& operator() (char c) ;

    string Print () ;

    void NextStep () ;

    void SkipStep (int i) ;

    void Reset () ;


};

#endif // LSYSTEM_H
