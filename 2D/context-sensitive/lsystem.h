#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Imagine/Graphics.h"
#include <stack>
#include <cmath>

using namespace std ;
using namespace Imagine ;


/****************************** LSYSTEM CONTEXT SENSITIVE **********************************/


/* On définit ici les L-Systems Context-sensitive. Pour simplifier l'écriture de la classe,
   on a choisi de ne traiter que le cas des (1,1)-systems. Le cas des (k,l)-sytems se traite
   de la même façon en rajoutant les paramètres k et l dans la définition de la classe. Il
   faut également remplacer */




// La structure Frame représente la position du repère au cours du tracé graphique. Les
// paramètres (x,y) correspondent aux coordonnées de l'origine dans la fenêtre. Le paramètre
// a représente l'inclinaison du repère. Enfin w permet de fixer l'épaisseur du prochain
// trait


struct Frame
{
  double x , y , a ;

  int w ;
  
  Frame() {} ;
  
  Frame (double X , double Y , double A , int W)
  {
      x = X , y = Y , a = A ;
      w = W ;
  } ;

} ;

class LSystem
{
  // LSystem intrinsèque

  string alphabet;
  
  string ignore ;
  
  string axiom;
  
  string tree;
  
  vector<string> *rules;
  
  vector<char> *left_context ;

  vector<char> *right_context ;
  
  string *rules_ign ;
  
  int step;

  // Paramètre d'affichage

  double rayon , angle ;
  
  int wdecroi;

  Frame origin ;

  stack<Frame> S ;
  
  Color col1 ;
  
  Color col2 ;
  
 public:
  
  LSystem();
  
  ~LSystem();
  
  LSystem(const string &ax, const string &al , const string& ign , Frame R , double r , double a , int wde , Color c1 , Color c2);

  int Step() ;
  
  void Affect(char c , char l_context , char r_context , string s) ;
  
  void Affect2 (char c , string s) ;
  
  string Print();

  bool Variable (char car) ;
  
  bool Ignore (char car) ;
  
  string Get (char car , char car_p , char car_s) ;
  
  void NextStep();
  
  void SkipStep(int i);
	
  void Reset();

  void Turtle_interpretation () ;
    
};

#endif // LSYSTEM_H
