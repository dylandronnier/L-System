#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Imagine/Graphics.h"
#include <stack>
#include <cmath>

using namespace std;
using namespace Imagine ;

/*********************L-system*********************/

/* On commence par définir une classe Lsystem qui permettra ensuite de coder différentes figures grâce aux arguments pris en compte. 
On inclut une structure Frame qui correspond aux conditions intiales du tracé du Lsystem (position où commence le tracé, l'orientation et la largeur du trait).*/

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

/* Dans la classe Lsystem, on définit toutes les caractéristiques propres aux Lsystem, qu'ils soient stochastiques ou non, à savoir l'alphabet et les constantes 
(regroupés dans la chaine de caractères alphabet), l'axiome de départ, l'arbre final, les règles et la probabilités associées à ces règles.
Pour stocker les probabilités et les règles associées à chaque caractère de l'alphabet, on a crée des tableaux de vecteurs. 
Le tableau de règles contient des vecteurs de chaines de caractères, qui correspondent à la règle associé à chaque caractère.
Le tableau de probabilités contient des vecteurs de probabilités (différentes segmentations de l'unité). */

class LSystem
{
  // LSystem intrinsèque

  string alphabet; //alphabet et constantes
  
  string axiom; // axiome de départ
  
  string tree; // enchainement de caractères constituant la figure finale
  
  vector<string> *rules; 
 
  vector<double> *proba; 
  
  int step; // étape d'itération

  // Paramètre d'affichage

  double rayon , angle ; // sert à définir la position dans le repère
  
  int wdecroi; // épaisseur du trait tracé

  Frame origin ;//initialisation du repère

  stack<Frame> S ; //repère mobile
  
  Color col1 ; // on définit deux couleurs pour faire des tracés bicolores.
  
  Color col2 ;
  
 public:
  
  LSystem();
  
  ~LSystem();
  
  LSystem(const string &ax, const string &al , Frame R , double r , double a , int wde , Color c1 , Color c2);

  int Step() ;
  
  void Affect(char c, double p, string s);
  
  string Print();
  
  void NextStep();
  
  void SkipStep(int i);
	
  void Reset();

  void Turtle_interpretation () ;
    
};

#endif // LSYSTEM_H
