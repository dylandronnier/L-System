#include "lsystem.h"

#define _USE_MATH_DEFINES


const double PI = M_PI ;

int main(int argc, char const *argv[])
{
  srand((unsigned int) time(0));
  
  openWindow(1280,700);
  
  
  /* Arbre_1 définition */
  
  LSystem Exemple
   (
    "abaaaaaaaaa", // Axiom
    "ab", // Alphabet
    "",
    Frame(600. , 695. , -PI/2. , 5) , // Origin
    5. , // Longeur trait
    PI / 5. , // Variation d'angle
    1, // Vitesse de décroissance de l'épaisseur des traits
    Color(134,93,45) , // Couleur principale 
    GREEN // Couleur secondaire
   ) ; 
   
    // Définition des règles :  
   
   Exemple.Affect('a','b',' ',"b");
   Exemple.Affect('b','a',' ',"a");
   
   cout << Exemple.Get('a','b',' ') << endl ;
   cout << Exemple.Get('a','a','b') << endl ;
   cout << Exemple.Variable('a') << endl ;
   
   Exemple.NextStep();
   //cout << Exemple.Print() << endl ;
   
   Exemple.NextStep();
   //cout << Exemple.Print() << endl ;
   
   Exemple.NextStep();
   //cout << Exemple.Print() << endl ;
   
     LSystem Arbre_1
   (
    "F1F1F1", // Axiom
    "01", // Alphabet
    "+-", // Ignore
    Frame(600. , 695. , -PI/2. , 1) , // Origin
    18. , // Longeur trait
    PI / 8. , // Variation d'angle
    0, // Vitesse de décroissance de l'épaisseur des traits
    Color(134,93,45) , // Couleur principale 
    GREEN // Couleur secondaire
   ) ;
   

   
   
   Arbre_1.Affect('0','0','0',"0");
   Arbre_1.Affect('0','0','1',"1[+F1F1]");
   Arbre_1.Affect('1','0','0',"1");
   Arbre_1.Affect('1','0','1',"1");
   Arbre_1.Affect('0','1','0',"0");
   Arbre_1.Affect('0','1','1',"1F1");
   Arbre_1.Affect('1','1','0',"0");
   Arbre_1.Affect('1','1','1',"0");
   Arbre_1.Affect2('+',"-");
   Arbre_1.Affect2('-',"+");
   
   Arbre_1.SkipStep(18);
   //cout<<Arbre_1.Print()<<endl ;
   Arbre_1.Turtle_interpretation();
   
   int x,y ;
   getMouse(x,y) ;
   fillRect(0,0,1280,700,WHITE);
   
        LSystem Arbre_2
   (
    "F1F1F1", // Axiom
    "01", // Alphabet
    "+-", // Ignore
    Frame(600. , 695. , -PI/2. , 1) , // Origin
    6. , // Longeur trait
    PI / 8. , // Variation d'angle
    0, // Vitesse de décroissance de l'épaisseur des traits
    Color(134,93,45) , // Couleur principale 
    GREEN // Couleur secondaire
   ) ; 
   
   
   Arbre_2.Affect('0','0','0',"1");
   Arbre_2.Affect('0','0','1',"1[-F1F1]");
   Arbre_2.Affect('1','0','0',"1");
   Arbre_2.Affect('1','0','1',"1");
   Arbre_2.Affect('0','1','0',"0");
   Arbre_2.Affect('0','1','1',"1F1");
   Arbre_2.Affect('1','1','0',"1");
   Arbre_2.Affect('1','1','1',"0");
   Arbre_2.Affect2('+',"-");
   Arbre_2.Affect2('-',"+");
   
   Arbre_2.SkipStep(30);
   //cout<<Arbre_2.Print()<<endl ;
   Arbre_2.Turtle_interpretation();

  
   
  endGraphics() ;
  
  return 0;
}
