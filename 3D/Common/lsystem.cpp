#include "lsystem.h"

LSystem::LSystem()
{
}


LSystem::~LSystem()
{
    delete[] rules ;
}

LSystem::LSystem(const string& ax, const string& al)
{
    axiom = tree = ax , alphabet = al ;
    rules = new string[al.size()] ;
    step = 0 ;
}

string& LSystem::operator () (int i)
{
    return rules[i];
}

string& LSystem::operator () (char c)
{
  return rules[alphabet.find(c)] ;
}

void LSystem::NextStep() // Fonction à modifier : Est-ce la méthode la plus rapide ?
{
    string buf_tree="" ;
    for (int i = 0  ; i<tree.size() ; i++ )
      buf_tree += operator()(tree[i]) ;
    tree = buf_tree ;
}

void LSystem::SkipStep(int i)
{
    for (int k=0 ; k<i ; k++)
        NextStep();
}

void LSystem::Reset()
{
    step = 0 ;
    tree = axiom ;
}

string LSystem::Print()
{
  return tree ;
}

