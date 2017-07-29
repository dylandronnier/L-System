#include "lsystem.h"

#define _USE_MATH_DEFINES


const double PI = 3.14159265;

int main(int argc, char const *argv[])
{
  srand((unsigned int) time(0));
  
  openWindow(1200,700);
  
  int x , y ;
  
  
  /* Arbre_1 définition */
  
  LSystem Arbre_1
    (
     "X", // Axiom
     "F[]+-X<>", // Alphabet
     Frame(520. , 630. , -PI/2. , 5) , // Origin
     5.0 , // Longeur trait
     PI / 5. , // Variation d'angle
     1, // Vitesse de décroissance de l'épaisseur des traits
     Color(134, 93, 45), // Couleur principale 
     GREEN // Couleur secondaire
     ) ; 
  
  // Définition des règles :
  
  Arbre_1.Affect('-', 1.0, "-");
  Arbre_1.Affect('+', 1.0, "+");
  Arbre_1.Affect(']', 1.0, "]");
  Arbre_1.Affect('[', 1.0, "[");
  Arbre_1.Affect('<', 1.0, "");
  Arbre_1.Affect('>', 1.0, "");
  Arbre_1.Affect('F', 1.0, "FF");
  Arbre_1.Affect('X', 0.5, "<F[++X]F[-X]+X>");
  Arbre_1.Affect('X', 0.5, "<F[+X]F[-X]+X>");

  Arbre_1.SkipStep(6);
  Arbre_1.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  
  /* Koch definition */
  
  LSystem Koch
    (
     "F", // Axiom
     "F+-", // Alphabet
     Frame(1000. , 550. , PI , 1) , // Origin
     0.4 , // Longeur trait
     PI / 2. , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(96,96,96) , // Couleur principale 
     WHITE // Couleur secondaire
     ) ;
  
  Koch.Affect('-',1.0,"-");
  Koch.Affect('+',1.0,"+");
  Koch.Affect('F',1.0,"F+F-F-F+F");
  
  Koch.SkipStep(7);
  Koch.Turtle_interpretation();

  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
   
  LSystem Dragon
    (
     "FX", // Axiom
     "F+-XY", // Alphabet
     Frame(300. , 450. , PI/2. , 1) , // Origin
     5. , // Longeur trait
     PI / 2. , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(28, 196, 236), // Couleur principale 
     WHITE // Couleur secondaire
     ) ;
   
  Dragon.Affect('-',1.0,"-");
  Dragon.Affect('+',1.0,"+");
  Dragon.Affect('F',1.0,"F");
  Dragon.Affect('X',1.0,"X+YF+");
  Dragon.Affect('Y',1.0,"-FX-Y");
  
  Dragon.SkipStep(14);
  Dragon.Turtle_interpretation();
   
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);

  /*
  LSystem Triangle
    (
     "X", // Axiom
     "F+-X", // Alphabet
     Frame(900., 650., PI, 2), // Origin
     5., // Longeur trait
     PI / 3., // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(190, 30, 72), // Couleur principale 
     WHITE // Couleur secondaire
     );
  
  Triangle.Affect('-', 1.0, "-");
  Triangle.Affect('+', 1.0, "+");
  Triangle.Affect('F', 1.0, "X+F+X");
  Triangle.Affect('X', 1.0, "F-X-F");
  
  Triangle.SkipStep(8);
  Triangle.Turtle_interpretation();

  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  */

  LSystem Tige
    (
     "F", // Axiom
     "F+-[]", // Alphabet
     Frame(600., 680., 3*PI/2., 3), // Origin
     2.6, // Longeur trait
     0.8, // Variation d'angle
     1, // Vitesse de décroissance de l'épaisseur des traits
     Color(190, 99, 5), // Couleur principale 
     WHITE // Couleur secondaire
     );

  Tige.Affect('-', 1.0, "-");
  Tige.Affect('+', 1.0, "+");
  Tige.Affect('[', 1.0, "[");
  Tige.Affect(']', 1.0, "]");
  Tige.Affect('F', 0.50, "F[+F][-F]F"); // kock.rules[pos(F) dans l'alphabet] =
  Tige.Affect('F', 0.30, "F[-F]F");
  Tige.Affect('F', 0.20, "F[+F]F");

  Tige.SkipStep(8);
  Tige.Turtle_interpretation();

  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  LSystem Church //il faut faire 7 itérations, sinon on n'obtient pas la figure de l'église désirée
    (
     "wxyz", // Axiom
     "F+-[]wxyz", // Alphabet
     Frame(800., 450., PI, 2), // Origin
     6., // Longeur trait
     PI/2., // Variation d'angle
     0., // Vitesse de décroissance de l'épaisseur des traits
     Color(150, 13, 160), // Couleur principale 
     WHITE // Couleur secondaire
     );

  Church.Affect('-', 1.0, "-");
  Church.Affect('+', 1.0, "+");
  Church.Affect('[', 1.0, "[");
  Church.Affect(']', 1.0, "]");
  Church.Affect('F', 1.0, ""); // kock.rules[pos(F) dans l'alphabet] =
  Church.Affect('x', 1.0, "Fw+F-z");
  Church.Affect('y', 1.0, "++F--y+F-z");
  Church.Affect('z', 1.0, "++F--y-F+x++F--y-F+x");
  Church.Affect('w', 1.0, "Fw+F-zFw-F+x");
  
  Church.SkipStep(7);
  Church.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);

  
  
  LSystem Cesaro
    (
     "F", // Axiom
     "F+-", // Alphabet
     Frame(1150., 500.,  PI, 2), // Origin
     2.5, // Longeur trait
     7 * PI / 16., // Variation d'angle
     0., // Vitesse de décroissance de l'épaisseur des traits
     Color(50, 13, 160), // Couleur principale 
     GREEN // Couleur secondaire
     );
  
  Cesaro.Affect('-', 1.0, "-");
  Cesaro.Affect('+', 1.0, "+");
  Cesaro.Affect('F', 1.0, "F+F--F+F");
  
  Cesaro.SkipStep(7);
  Cesaro.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  LSystem Chaine
    (
	    "F-F-F-F", // Axiom
	    "F+-", // Alphabet
	    Frame(700., 550., 0., 1), // Origin
	    3.5, // Longeur trait
	    PI/2., // Variation d'angle
	    0., // Vitesse de décroissance de l'épaisseur des traits
	    Color(153, 141, 84), // Couleur principale 
	    WHITE // Couleur secondaire
     );
  
  Chaine.Affect('-', 1.0, "-");
  Chaine.Affect('+', 1.0, "+");
  Chaine.Affect('F', 1.0, "FF-F-F-F-F-F+F");
  
  Chaine.SkipStep(4) ;
  Chaine.Turtle_interpretation() ;
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  LSystem Plant2
    (
     "F", // Axiom
     "F+-[]", // Alphabet
     Frame(500. , 680. , 3*PI/2. , 1) , // Origin
     2.7 , // Longeur trait
     0.45 , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(28, 196, 236), // Couleur principale 
     WHITE // Couleur secondaire
     ) ;
  
  Plant2.Affect('-',1.0,"-");
  Plant2.Affect('+',1.0,"+");
  Plant2.Affect('F',1.0,"F[+F]F[-F]F");
  Plant2.Affect('[', 1.0, "[");
  Plant2.Affect(']', 1.0, "]");
  
  Plant2.SkipStep(5);
  Plant2.Turtle_interpretation();
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  

  LSystem Plant3
    (
     "F", // Axiom
     "F+-[]<>", // Alphabet
     Frame(500. , 680. , 3*PI/2. , 1) , // Origin
     10. , // Longeur trait
     0.45 , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(28, 196, 236), // Couleur principale 
     Color(150, 96, 236)  // Couleur secondaire
     ) ;
  
  Plant3.Affect('-',1.0,"-");
  Plant3.Affect('+',1.0,"+");
  Plant3.Affect('<', 1.0, "");
  Plant3.Affect('>', 1.0, "");
  Plant3.Affect('F',1.0,"F<[+F]>F<[-F]>[F]");
  Plant3.Affect('[', 1.0, "[");
  Plant3.Affect(']', 1.0, "]");
  
  Plant3.SkipStep(5);
  Plant3.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);

  /*
  LSystem Plant3a
    (
     "F", // Axiom
     "F+-[]<>", // Alphabet
     Frame(200. , 680. , 3*PI/2. , 1) , // Origin
     10. , // Longeur trait
     0.45 , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(28, 196, 236), // Couleur principale 
     Color(150, 96, 236)  // Couleur secondaire
     ) ;
  
  Plant3a.Affect('-',1.0,"-");
  Plant3a.Affect('+',1.0,"+");
  Plant3a.Affect('<', 1.0, "");
  Plant3a.Affect('>', 1.0, "");
  Plant3a.Affect('F',1.0,"F<[+F]>F<[-F]>[F]");
  Plant3a.Affect('[', 1.0, "[");
  Plant3a.Affect(']', 1.0, "]");
  
  Plant3a.SkipStep(5);
  Plant3a.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  */
  
  LSystem Plant4
    (
     "X", // Axiom
     "F+-[]<>X", // Alphabet
     Frame(600. , 680. , 3*PI/2. , 1) , // Origin
     1.9 , // Longeur trait
     -0.39 , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(24, 196, 23), // Couleur principale 
     WHITE  // Couleur secondaire
     ) ;
  
  Plant4.Affect('-',1.0,"-");
  Plant4.Affect('+',1.0,"+");
  Plant4.Affect('<', 1.0, "");
  Plant4.Affect('>', 1.0, "");
  Plant4.Affect('X',1.0,"F-[[X]+X]+F[+FX]-X");
  Plant4.Affect('F', 1.0, "FF");
  Plant4.Affect('[', 1.0, "[");
  Plant4.Affect(']', 1.0, "]");

  Plant4.SkipStep(7);
  Plant4.Turtle_interpretation();

  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  LSystem Plant
	   (
	    "F", // Axiom
	    "F+-[]<>", // Alphabet
	    Frame(600., 650., 3*PI / 2., 1), // Origin
	    5.5, // Longeur trait
	    2*PI / 16., // Variation d'angle
	    0., // Vitesse de décroissance de l'épaisseur des traits
	    Color(12, 150, 90), // Couleur principale 
	    GREEN // Couleur secondaire
	    );
  
  Plant.Affect('-', 1.0, "-");
  Plant.Affect('+', 1.0, "+");
  Plant.Affect('<', 1.0, "");
  Plant.Affect('>', 1.0, "");
  Plant.Affect('[', 1.0, "[");
  Plant.Affect(']', 1.0, "]");
  Plant.Affect('F', 1.0, "FF-[-F+F<+F>]+[+F-F<-F>]");
  
  Plant.SkipStep(5);
  Plant.Turtle_interpretation();
  
  getMouse(x,y) ;
  fillRect(0,0,1200,700,WHITE);
  
  LSystem Plant5
    (
     "X", // Axiom
     "F+-[]<>X", // Alphabet
     Frame(600. , 680. , 3*PI/2. , 1) , // Origin
     2.5 , // Longeur trait
     0.49 , // Variation d'angle
     0, // Vitesse de décroissance de l'épaisseur des traits
     Color(24, 196, 103), // Couleur principale 
     WHITE  // Couleur secondaire
     ) ;
  
  Plant5.Affect('-',1.0,"-");
  Plant5.Affect('+',1.0,"+");
  Plant5.Affect('<', 1.0, "");
  Plant5.Affect('>', 1.0, "");
  Plant5.Affect('X',1.0,"F[+X][-X]FX");
  Plant5.Affect('F', 1.0, "FF");
  Plant5.Affect('[', 1.0, "[");
  Plant5.Affect(']', 1.0, "]");
  
  Plant5.SkipStep(7);
  Plant5.Turtle_interpretation();
  
  endGraphics();
  return 0;
}
