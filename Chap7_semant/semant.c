#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

//////////////////////////////////////
// the symbol table structured as a list
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

// construct a id table
void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

Type_t check_exp (Exp_t exp)
{
	switch (exp->kind)
	{
	case(EXP_INT) : return TYPE_INT;
	case(EXP_TRUE) :
	case(EXP_FALSE) : return TYPE_BOOL;
	case(EXP_ID) : {
					   Exp_Id p = (Exp_Id)exp;
					   if (Table_lookup(p->id) == -1){
						   fprintf(stderr, "Error: the variable "
							   "\"%s\" has not been declared!\n", p->id);
						   exit(0);
					   }
					   else{
						   return Table_lookup(p->id);
					   }
	}
	case(EXP_ADD) : {
						Exp_Add p = (Exp_Add)exp;
						Type_t t1 = check_exp(p->left);
						Type_t t2 = check_exp(p->right);
						if (t1 != TYPE_INT || t2 != TYPE_INT){
							fprintf(stderr, "operator + must be used between two integers\n");
							exit(0);
						}
						else return TYPE_INT;
	}
	case(EXP_SUB) : {
						Exp_Sub p = (Exp_Sub)exp;
						Type_t t1 = check_exp(p->left);
						Type_t t2 = check_exp(p->right);
						if (t1 != TYPE_INT || t2 != TYPE_INT){
							fprintf(stderr, "operator - must be used between two integers\n");
							exit(0);
						}
						else return TYPE_INT;
	}
	case(EXP_TIMES) : {
						Exp_Times p = (Exp_Times)exp;
						Type_t t1 = check_exp(p->left);
						Type_t t2 = check_exp(p->right);
						if (t1 != TYPE_INT || t2 != TYPE_INT){
							fprintf(stderr, "operator * must be used between two integers\n");
							exit(0);
						}
						else return TYPE_INT;
	}
	case(EXP_DIVIDE) : {
						  Exp_Divide p = (Exp_Divide)exp;
						  Type_t t1 = check_exp(p->left);
						  Type_t t2 = check_exp(p->right);
						  if (t1 != TYPE_INT || t2 != TYPE_INT){
							  fprintf(stderr, "operator * must be used between two integers\n");
							  exit(0);
						  }
						  Exp_Int q = (Exp_Int)(p->right);
						  if (q->n == 0){
							  fprintf(stderr, "divide by 0 error\n");
							  exit(0);
						  }
						  else return TYPE_INT;
	}
	case(EXP_AND) : {
						  Exp_And p = (Exp_And)exp;
						  Type_t t1 = check_exp(p->left);
						  Type_t t2 = check_exp(p->right);
						  if (t1 != TYPE_BOOL || t2 != TYPE_BOOL){
							  fprintf(stderr, "operator && must be used between two booleans\n");
							  exit(0);
						  }
						  else return TYPE_BOOL;
	}
	case(EXP_OR) : {
						Exp_Or p = (Exp_Or)exp;
						Type_t t1 = check_exp(p->left);
						Type_t t2 = check_exp(p->right);
						if (t1 != TYPE_BOOL || t2 != TYPE_BOOL){
							fprintf(stderr, "operator || must be used between two booleans\n");
							exit(0);
						}
						else return TYPE_BOOL;
	}
	default:{
				fprintf(stderr, "semant error in expression\n");
				exit(0);
	}
	}
}

////////////////////////////////////////
// stm
void check_stm (Stm_t stm)
{
	switch (stm->kind){
	case(STM_ASSIGN) : {
						   Stm_Assign p = (Stm_Assign)stm;
						   if (Table_lookup(p->id) != check_exp(p->exp)){
							   fprintf(stderr, "parameters of assign statments should have same id\n");
							   exit(0);
						   }
						   return;
	}
	case(STM_PRINTI) : {
						   Stm_Printi p = (Stm_Printi)stm;
						   if (check_exp(p->exp) != TYPE_INT){
							   fprintf(stderr, "parameters of printi statments should be integers\n");
							   exit(0);
						   }
						   return;
	}
	case(STM_PRINTB) : {
						   Stm_Printb p = (Stm_Printb)stm;
						   if (check_exp(p->exp) != TYPE_INT){
							   fprintf(stderr, "parameters of printb statments should be booleans\n");
							   exit(0);
						   }
						   return;
	}
	default:{
				fprintf(stderr, "semant error in statements\n");
				exit(0);
	}
	}
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
