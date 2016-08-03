#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

// "constructors"
Exp_t Exp_Int_new (int n)
{
  Exp_Int p = (Exp_Int)malloc (sizeof (*p));
  p->kind = EXP_INT;
  p->n = n;
  return (Exp_t)p;
}

Exp_t Exp_Add_new (Exp_t left, Exp_t right)
{
  Exp_Add p = (Exp_Add)malloc (sizeof (*p));
  p->kind = EXP_ADD;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Sub_new (Exp_t left, Exp_t right)
{
  Exp_Sub p = (Exp_Sub)malloc (sizeof (*p));
  p->kind = EXP_SUB;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Times_new (Exp_t left, Exp_t right)
{
  Exp_Times p = (Exp_Times)malloc (sizeof (*p));
  p->kind = EXP_TIMES;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Div_new (Exp_t left, Exp_t right)
{
  Exp_Div p = (Exp_Div)malloc (sizeof (*p));
  p->kind = EXP_DIV;
  p->left = left;
  p->right = right;
  return (Exp_t)p;
}

Exp_t Exp_Par_new (Exp_t content)
{
  Exp_Par p = (Exp_Par)malloc (sizeof (*p));
  p->kind = EXP_PAR;
  p->content = content;
  return (Exp_t)p;
}

// all operations on "Exp"
void Exp_print (Exp_t exp)
{
  switch (exp->kind){
  case EXP_INT:{
    Exp_Int p = (Exp_Int)exp;
    printf ("%d", p->n);
    return;
  }
  case EXP_ADD:{
    Exp_Add p = (Exp_Add)exp;
    //printf ("(");
    Exp_print (p->left);
    printf(" + ");
    //printf (") + (");
    Exp_print (p->right);
    //printf (")");
    return;
  }
  case EXP_SUB:{
    Exp_Sub p = (Exp_Sub)exp;
    //printf ("(");
    Exp_print (p->left);
    printf(" - ");
    //printf (") - (");
    Exp_print (p->right);
    //printf (")");
    return;
  }
  case EXP_TIMES:{
    Exp_Times p = (Exp_Times)exp;
    //printf ("(");
    Exp_print (p->left);
    printf(" * ");
    //printf (") * (");
    Exp_print (p->right);
    //printf (")");
    return;
  }
  case EXP_DIV:{
    Exp_Div p = (Exp_Div)exp;
    //printf ("(");
    Exp_print (p->left);
    printf(" / ");
    //printf (") * (");
    Exp_print (p->right);
    //printf (")");
    return;
  }
  case EXP_PAR:{
    Exp_Par p = (Exp_Par)exp;
    printf ("(");
    Exp_print (p->content);
    printf (")");
    return;
  }
  default:
    return;
  }
}

int Exp_numNodes (Exp_t exp){
  switch (exp->kind){
  case EXP_INT:{
  	return 1;
  }
  case EXP_ADD:{
  	Exp_Add p = (Exp_Add)exp;
  	return 1 + Exp_numNodes(p->left) + Exp_numNodes(p->right);
  }
  case EXP_SUB:{
  	Exp_Sub p = (Exp_Sub)exp;
  	return 1 + Exp_numNodes(p->left) + Exp_numNodes(p->right);
  }
  case EXP_TIMES:{
  	Exp_Times p = (Exp_Times)exp;
  	return 1 + Exp_numNodes(p->left) + Exp_numNodes(p->right);
  }
  case EXP_DIV:{
  	Exp_Div p = (Exp_Div)exp;
  	return 1 + Exp_numNodes(p->left) + Exp_numNodes(p->right); 
  }
  case EXP_PAR:{
  	Exp_Par p = (Exp_Par)exp;
  	return 1 + Exp_numNodes(p->content); 
  }
  default:
    return 0;
  }	
}



