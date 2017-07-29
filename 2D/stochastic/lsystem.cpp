#include "lsystem.h"


/********************************LSystem*********************************/


LSystem::LSystem()
{
}


LSystem::~LSystem()
{
  delete[] rules;
  delete[] proba;
}


LSystem::LSystem(const string& ax, const string& al , Frame R , double r , double a , int wde , Color c1 , Color c2)
{
  axiom = tree = ax, alphabet = al;
  rules = new vector<string>[al.size()];
  proba = new vector<double>[al.size()];
  step = 0;
  origin = R ;
  rayon = r ;
  angle = a ;
  col1 = c1 ;
  col2 = c2 ;
  wdecroi = wde ;
  
}


int LSystem::Step()
{
  return step ;

}


//Cette fonction permet de rajouter la règle et la probabilité correspondant à un caractère de l'alphabet dans les tableaux prévus à cet effet;
//s correspond à la règle associée au caractère, tandis que p est la probabilité de cette règle.

void LSystem::Affect(char c, double p, string s)
{
  int i = alphabet.find(c);
  rules[i].push_back(s);
  proba[i].push_back(p);
}

//locpos modélise une probabilité discrète à partir d'une probabilité uniforme.
int locpos(const vector<double> &v, double pr)
{
  int res = 0;
  while (pr > v[res])
    {
      pr = pr - v[res];
      res++;
    }
  return res;
}


// Cette fonction permet de parcourir la chaine de caractère et d'associer à chaque caractère son interprétation et sa probabilité,
//et on remplace ensuite l'ancienne chaine de caractère par la nouvelle.

void LSystem::NextStep()
{
  double p; // probabilité uniforme sur [0;1] 
  string buf_tree = ""; // ceci stockera l'arbre au fur et à mesure des itérations.
  int j;
  for (int i = 0; i<tree.size(); i++)
    {
      j = alphabet.find(tree[i]);
      p = double(rand()) / double(RAND_MAX);
      buf_tree += rules[j][locpos(proba[j], p)];
    }
  tree = buf_tree;
  
}

//Cette fonction code le nombre d'itérations que l'on fera pour nos figures. Un itération correspond à un parcours de la chaine de caractère actuelle (donc le buf tree)
//en les interprétant.

void LSystem::SkipStep(int i)
{
  for (int k = 0; k<i; k++)
    NextStep();
}

void LSystem::Reset()
{
  step = 0;
  tree = axiom;
}

string LSystem::Print()
{
  return tree;
}

// Cette fonction permet d'interpréter toutes les constantes ainsi que l'alphabet utilisé dans un LSystem. 
void LSystem::Turtle_interpretation () 
{
  Frame R = origin ;
  double nx , ny ;
  Color col = col1 ;

  for (int i = 0 ; i < tree.size() ; i++)
  {
      
      switch (tree[i]) {
	
	case '>' : 
	  col = col1 ;
	break ;
	
	case '<' : 
	  col = col2;
	break ;
	// on trace le segment correspondant à la variable F:
      case 'F' :
	
	nx=R.x+rayon*cos(R.a);
	ny=R.y+rayon*sin(R.a);
	
	drawLine(R.x , R.y , nx , ny , col, R.w);
	R.x=nx;
	R.y=ny;
	break;
	
	// Le + effectuera la rotation dans le sens positif, et il diminuera l'épaisseur du trait tracé ensuite:
      case '+' : 
	
	R.a += angle ;
	R.w -= wdecroi;
	break ;
	
// Le - effectuera la rotation dans le sesns négatif et il diminuera l'épaisseur du trait tracé ensuite:
 
     case '-' :
	R.a -= angle ;
	R.w -= wdecroi;
	break ;
	
	// Le [ stock la position actuelle, ainsi que l'angle et l'épaisseur afin de pouvoir y revenir ensuite et recommencer une nouvelle branche issue d'un même point.
      case '[':
	
	S.push(R); break;
	
	// Le ] revient à la dernière position stockée, ainsi qu'au dernier angle et à la dernière épaisseur stockée afin que toutes les branches partant d'un même point aient les mêmes propriétés. On elève également le premier élément des piles.
      case ']':
	
	R= S.top() ;
	S.pop() ;
	break;
    
      default:break;
      }
    }
  
}
