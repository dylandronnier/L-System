#include "lsystem.h"

LSystem::LSystem()
{
}


LSystem::~LSystem()
{
  delete[] rules ;
  delete[] left_context ;
  delete[] right_context ;
  delete[] rules_ign ;
}

LSystem::LSystem(const string& ax, const string& al , const string& ign, Frame R , double r , double a , int wde , Color c1 , Color c2)
{
  axiom = tree = ax , alphabet = al , ignore =ign ;
  rules = new vector<string>[al.size()] ;
  rules_ign = new string[ign.size()];
  left_context = new vector<char>[al.size()] ;
  right_context = new vector<char>[al.size()] ;
  step = 0 ;
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

void LSystem::Affect(char c , char l_context , char r_context , string s)
{
  int i = alphabet.find(c) ;
  rules[i].push_back(s) ;
  left_context[i].push_back(l_context) ;
  right_context[i].push_back(r_context) ;
}

void LSystem::Affect2(char c, string s)
{
  rules_ign[ignore.find(c)] = s ;

}


bool LSystem::Variable (char car)
{
  bool b = false ;
  for (int i = 0 ; i < alphabet.size() ; i++)
    b = b || (car == alphabet[i]) ;
  return b ;
}

bool LSystem::Ignore (char car)
{
  bool b = false ;
  for (int i = 0 ; i < ignore.size() ; i++)
    b = b || (car == ignore[i]) ;
  return b ;
}


string LSystem::Get (char car , char car_p , char car_s)
{ 
  string res ="" ;
  res += car ;
  if (Variable(car))
    {
      int j = alphabet.find(car) ;
      for (int k = 0 ; k < left_context[j].size() ; k++)
	if ( (left_context[j][k] == car_p || left_context[j][k] == ' ') &&
	      (right_context[j][k] == car_s || right_context[j][k] == ' '))
	  res = rules[j][k] ; 
      
    }
    else if (Ignore(car))
      res = rules_ign[ignore.find(car)];

  return res ;
  
}


void LSystem::NextStep()
{
  int sz = tree.size() ;
  string buf_tree = "" ;

  char tmp = ' ' ;
  
  vector<char> prec ;
  vector<char> suiv ;

  stack<char> sauv ;
  

  for (int i=0 ; i<sz ; i++)
  {
    prec.push_back(tmp) ;
    if (Variable(tree[i]))
       tmp = tree[i] ;
    else if (tree[i] == '[')
      sauv.push(tmp) ;
    else if (tree[i] == ']')
      { tmp = sauv.top() ; sauv.pop() ;}
  }
  tmp = ' ' ;

  for (int i=sz - 1 ; i>=0 ; i--)
  {
    suiv.push_back(tmp) ;
    if (Variable(tree[i]))
       tmp = tree[i] ;
    else if (tree[i] == ']')
      sauv.push(tmp) ;
    else if (tree[i] == '[')
      { tmp = sauv.top() ; sauv.pop() ;}
  }
      

  for (int i = 0; i<sz; i++)
    {
      buf_tree += Get(tree[i] , prec[i] , suiv[i]) ;
    }
  tree = buf_tree;
  
}

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

	// on trace le segment correspondant à la variable F :

      case 'F' :
	
	nx=R.x+rayon*cos(R.a);
	ny=R.y+rayon*sin(R.a);
	
	drawLine(R.x , R.y , nx , ny , col, R.w);
	R.x=nx;
	R.y=ny;
	break;
	
	// Le + effectuera la rotation dans le sens positif, et il diminuera l'épaisseur du trait tracé ensuite :

      case '+' : 
	
	R.a += angle ;
	R.w -= wdecroi;
	break ;
	
	// Le - effectuera la rotation dans le sesns négatif et il diminuera l'épaisseur du trait tracé ensuite :
 
     case '-' :
	R.a -= angle ;
	R.w -= wdecroi;
	break ;
	
	// Le [ stock la position actuelle, ainsi que l'angle et l'épaisseur afin de pouvoir y revenir ensuite et 
	// recommencer une nouvelle branche issue d'un même point.

      case '[':
	
	S.push(R); break;
	
	// Le ] revient à la dernière position stockée, ainsi qu'au dernier angle et à la dernière épaisseur stockée 
	// afin que toutes les branches partant d'un même point aient les mêmes propriétés. On elève également le premier
	// élément des piles.

      case ']':
	
	R= S.top() ;
	S.pop() ;
	break;
    
      default:break;
      }
    }
  
}
