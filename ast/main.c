#include "ast.h"

extern Exp_t tree;
void yyparse ();

int main (int argc, char **argv)
{
  yyparse();
  if(tree){
  	Exp_print (tree);
  	printf("\n");
  	int num = Exp_numNodes (tree);
  	printf("NumNodes: %d\n", num);
  }
  else{
  	printf("No tree generated.\n");
  }
  system("pause"); 
  return 0;
}
