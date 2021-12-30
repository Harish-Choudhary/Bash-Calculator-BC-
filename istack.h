#ifndef stack_H_INCLUDED
#define stack_H_INCLUDED


#include "list.h"


typedef struct inode {
	number *a;
	struct inode *p;
}inode;
typedef inode *stack;
void initnumstack(stack *s);

void pushnum(stack *s, number *a);

number *popnum(stack *s);

int isemptynumstack(stack *s);


typedef struct cnode {
	char a;
	struct cnode *p;
}cnode;
typedef cnode *opstack;
void initopstack(opstack *s);

void pushop(opstack *s, char t);
char topop(opstack*s);
char pop_op(opstack *s);
int isemptyopstack(opstack *s);
#endif
