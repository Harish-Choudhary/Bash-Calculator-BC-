#include<stdlib.h>
#include"istack.h"


void initnumstack(stack *s) {
	*s = NULL;
}
void pushnum (stack *s, number *t) {
	stack temp;
	temp = (inode *)malloc(sizeof(inode));
	temp->a = t;
	temp->p = *s;
	*s = temp;
}
number *popnum(stack *s) {
	number *t;
	stack temp;
	t = (*s)->a;
	temp = *s;
	*s = (*s)->p;
	free(temp);
	return t;
}
int isemptynumstack (stack *s) {
	return *s == NULL;
}


void initopstack(opstack *s) {
	*s = NULL;
}
void pushop (opstack *s, char t) {
	opstack temp;
	temp = (cnode *)malloc(sizeof(cnode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}
char pop_op(opstack *s) {
	char t;
	opstack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}
char topop(opstack *s) {
	char ch;
	ch = pop_op(s);
	pushop(s, ch);
	return ch;
}
int isemptyopstack (opstack *s) {
	return *s == NULL;
}
